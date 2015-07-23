#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/IOInterface.h"
#include "Image.h"

#include "libjpeg\jpeglib.h"
#include "libjpeg\jerror.h"

using Neutron::Engine::Image;
using Neutron::Engine::ImagePtr;
using Neutron::Utility::IOInterface;

namespace Neutron
{
	namespace System
	{
		namespace File
		{
			class NEUTRON_CORE FileJPEG
			{
				struct jerror_mgr
				{
					struct jpeg_error_mgr pub;
					jmp_buf setjmp_buffer;
				};

				struct FileSource
				{
					jpeg_source_mgr pub;
					JOCTET buffer[4096];
					IOInterface* file;
				};

				struct FileDestination
				{
					jpeg_destination_mgr pub;
					JOCTET buffer[4096];
					IOInterface* file;
				};

				static void setFileSource( j_decompress_ptr decompress, IOInterface* file );
				static void initSource( j_decompress_ptr decompress );
				static void termSource( j_decompress_ptr decompress );
				static uint8 fillInputBuffer( j_decompress_ptr decompress );
				static void skipInputData( j_decompress_ptr decompress, long numBytes );
				static void initDestination( j_compress_ptr compress );
				static void termDestination( j_compress_ptr compress );
				static uint8 emptyOutputBuffer( j_compress_ptr compress );
				static void errorExit( j_common_ptr common );
				static void outputMessage( j_common_ptr common );

			public:
				FileJPEG();
				virtual ~FileJPEG();

				static ImagePtr load( const char* path );
				static void save( const ImagePtr image, const char* path, float quality );
			};
		}
	}
}