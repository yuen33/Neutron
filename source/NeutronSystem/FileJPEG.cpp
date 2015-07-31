#include "FileJPEG.h"
#include "PixelFormat.h"
#include "Log.h"
#include "NeutronEngine.h"

using Neutron::Utility::IOStdFile;

namespace Neutron
{
	namespace System
	{
		namespace File
		{
			FileJPEG::FileJPEG()
			{
			}

			FileJPEG::~FileJPEG()
			{
			}

			ImagePtr FileJPEG::load( const char* path )
			{
				IOStdFile* file = new IOStdFile( path, "rb" );
				if( !file )
				{
					return ImagePtr::null;
				}

				if( !file->isValid() )
				{
					delete file;
					return ImagePtr::null;
				}

				ImagePtr image;

				jpeg_decompress_struct decompress;
				jerror_mgr jerror;
				decompress.err = jpeg_std_error( &jerror.pub );
				jerror.pub.error_exit = errorExit;
				jerror.pub.output_message = outputMessage;
				if( setjmp( jerror.setjmp_buffer ) )
				{
					jpeg_destroy_decompress( &decompress );
					delete file;
					return false;
				}

				jpeg_create_decompress( &decompress );
				setFileSource( &decompress, file );
				jpeg_read_header( &decompress, true );
				jpeg_start_decompress( &decompress );

				if( decompress.output_components == 1 )
				{
					image = Engine::getEngine().getResourceManager().createImage2D( decompress.image_width, decompress.image_height, Engine::Render::PF_R8UN, 1, 1 );
					//image = Image::create2D( decompress.image_width, decompress.image_height, Engine::Render::PF_R8UN, 1, 1 );
				}
				else if( decompress.output_components == 3 )
				{
					image = Engine::getEngine().getResourceManager().createImage2D( decompress.image_width, decompress.image_height, Engine::Render::PF_RGB8UN, 1, 1 );
					//image = Image::create2D( decompress.image_width, decompress.image_height, Engine::Render::PF_RGB8UN, 1, 1 );
				}
				
				if( image.isNull() )
				{
					jpeg_finish_decompress( &decompress );
					jpeg_destroy_decompress( &decompress );
					delete file;
					return ImagePtr::null;
				}

				uint8* data = image->getData();
				int stride = decompress.output_width * decompress.output_components;
				while( decompress.output_scanline < decompress.output_height )
				{
					jpeg_read_scanlines( &decompress, &data, 1 );
					data += stride;
				}

				jpeg_finish_decompress( &decompress );
				jpeg_destroy_decompress( &decompress );
				delete file;

				return image;
			}

			void FileJPEG::save( ImagePtr image, const char* path, float quality )
			{
				if( image->getResourceType() != Image::IT_2D )
				{
					return;
				}

				jpeg_compress_struct compress;
				jerror_mgr jerror;
				compress.err = jpeg_std_error( &jerror.pub );
				jerror.pub.error_exit = errorExit;
				jerror.pub.output_message = outputMessage;
				if( setjmp( jerror.setjmp_buffer ) )
				{
					return;
				}

				jpeg_create_compress( &compress );
				compress.image_width = image->getWidth();
				compress.image_height = image->getHeight();
				
				if( image->getFormat() == Engine::Render::PF_R8UN )
				{
					compress.input_components = 1;
					compress.in_color_space = JCS_GRAYSCALE;
				}
				else if( image->getFormat() == Engine::Render::PF_RGB8UN )
				{
					compress.input_components = 3;
					compress.in_color_space = JCS_RGB;
				}
				else
				{
					jpeg_destroy_compress( &compress );
					return;
				}

				IOStdFile* file = new IOStdFile( path, "wb" );
				if( !file )
				{
					return;
				}

				compress.dest = (jpeg_destination_mgr*)( *compress.mem->alloc_small )( (j_common_ptr)&compress, JPOOL_PERMANENT, sizeof( FileDestination ) );
				FileDestination* dest = (FileDestination*)compress.dest;
				dest->pub.init_destination = initDestination;
				dest->pub.term_destination = termDestination;
				dest->pub.empty_output_buffer = emptyOutputBuffer;
				dest->file = file;

				jpeg_set_defaults( &compress );
				jpeg_set_quality( &compress, (int)( quality * 100.0f ), true );

				jpeg_start_compress( &compress, true );
				const uint8* data = image->getData();
				Size stride = image->getWidth() * Engine::Render::getFormatSize( image->getFormat() );
				while( compress.next_scanline < compress.image_height )
				{
					JSAMPROW ptr = (JSAMPROW)&data[compress.next_scanline * stride];
					jpeg_write_scanlines( &compress, &ptr, 1 );
				}
				jpeg_finish_compress( &compress );
				jpeg_destroy_compress( &compress );

				delete file;
			}

			void FileJPEG::setFileSource( j_decompress_ptr decompress, IOInterface* file )
			{
				decompress->src = (jpeg_source_mgr*)(*decompress->mem->alloc_small )( (j_common_ptr)decompress, JPOOL_PERMANENT, sizeof( FileSource ) );
				FileSource* src = (FileSource*)decompress->src;
				src->pub.init_source = initSource;
				src->pub.term_source = termSource;
				src->pub.fill_input_buffer = fillInputBuffer;
				src->pub.skip_input_data = skipInputData;
				src->pub.resync_to_restart = jpeg_resync_to_restart;
				src->pub.bytes_in_buffer = 0;
				src->pub.next_input_byte = 0;
				src->file = file;
			}

			void FileJPEG::initSource( j_decompress_ptr decompress )
			{
			}

			void FileJPEG::termSource( j_decompress_ptr decompress )
			{
			}

			uint8 FileJPEG::fillInputBuffer( j_decompress_ptr decompress )
			{
				FileSource* src = (FileSource*)decompress->src;
				Size size = src->file->read( src->buffer, sizeof( src->buffer ) );
				if( size <= 0 )
				{
					if( src->file->getSize() == 0 )
					{
						ERREXIT( decompress, JERR_INPUT_EMPTY );
					}
					WARNMS( decompress, JWRN_JPEG_EOF );
					src->buffer[0] = (JOCTET)0xff;
					src->buffer[1] = (JOCTET)JPEG_EOI;
					size = 2;
				}
				src->pub.next_input_byte = src->buffer;
				src->pub.bytes_in_buffer = size;

				return true;
			}

			void FileJPEG::skipInputData( j_decompress_ptr decompress, long numBytes )
			{
				if( numBytes > 0 )
				{
					FileSource* src = (FileSource*)decompress->src;
					while( numBytes > (long)src->pub.bytes_in_buffer )
					{
						numBytes -= (long)src->pub.bytes_in_buffer;
						fillInputBuffer( decompress );
					}
					src->pub.next_input_byte += numBytes;
					src->pub.bytes_in_buffer -= numBytes;
				}
			}

			void FileJPEG::errorExit( j_common_ptr common )
			{
				(*common->err->output_message )( common );
			}

			void FileJPEG::outputMessage( j_common_ptr common )
			{
				char msg[JMSG_LENGTH_MAX];
				(*common->err->format_message)( common, msg );
				Log::error( "FileJPEG", msg );
			}

			void FileJPEG::initDestination( j_compress_ptr compress )
			{
				FileDestination* dest = (FileDestination*)compress->dest;
				dest->pub.next_output_byte = dest->buffer;
				dest->pub.free_in_buffer = sizeof( dest->buffer );
			}

			void FileJPEG::termDestination( j_compress_ptr compress )
			{
				FileDestination* dest = (FileDestination*)compress->dest;
				Size bytes = sizeof( dest->buffer ) - dest->pub.free_in_buffer;
				if( bytes > 0 && dest->file->write( dest->buffer, bytes ) != bytes )
				{
					ERREXIT( compress, JERR_FILE_WRITE );
				}
			}

			uint8 FileJPEG::emptyOutputBuffer( j_compress_ptr compress )
			{
				FileDestination* dest = (FileDestination*)compress->dest;
				Size bytes = dest->file->write( dest->buffer, sizeof( dest->buffer ) );
				if( bytes != sizeof( dest->buffer ) )
				{
					ERREXIT( compress, JERR_FILE_WRITE );
				}
				dest->pub.next_output_byte = dest->buffer;
				dest->pub.free_in_buffer = sizeof( dest->buffer );
				return true;
			}
		}
	}
}