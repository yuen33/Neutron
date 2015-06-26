#include "FileJPEG.h"

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
				IOStdFile* file = new IOStdFile( path, "r" );
				if( !file )
				{
					return ImagePtr::null();
				}

				if( !file->isValid() )
				{
					delete file;
					return ImagePtr::null();
				}

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
				}
			}
		}
	}
}