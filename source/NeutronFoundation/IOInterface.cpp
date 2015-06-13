#include "IOInterface.h"

namespace Neutron
{
	namespace Utility
	{
		IOStdFile::IOStdFile( const char* filepath, const char* mode )
			:file( 0 )
		{
			assert( filepath && mode );
			errno_t err = fopen_s( &file, filepath, mode );
			if( !err && file )
			{
				path = filepath;
			}
		}

		IOStdFile::~IOStdFile()
		{
			if( file )
			{
				fclose( file );
			}

			path.clear();
		}

		void IOStdFile::seekSet( int offset )
		{
			if( file )
			{
				::fseek( file, offset, SEEK_SET );
			}
		}

		void IOStdFile::seekEnd( int offset )
		{
			if( file )
			{
				::fseek( file, offset, SEEK_END );
			}
		}

		void IOStdFile::seekCur( int offset )
		{
			if( file )
			{
				::fseek( file, offset, SEEK_CUR );
			}
		}

		Size IOStdFile::tell() const
		{
			return ::ftell( file );
		}

		boolean IOStdFile::eof() const
		{
			return ::feof( file ) != 0;
		}

		void IOStdFile::flush()
		{
			::fflush( file );
		}

		Size IOStdFile::read( uint8* buffer, Size size )
		{
			return ::fread( buffer, 1, size, file );
		}

		Size IOStdFile::write( uint8* buffer, Size size )
		{
			return ::fwrite( buffer, 1, size, file );
		}

		Size IOStdFile::getSize() const
		{
			Size oldOffset = ftell( file );
			::fseek( file, 0, SEEK_END );
			Size size = ftell( file );
			::fseek( file, oldOffset, SEEK_SET );
			return size;
		}

		// IOMemory
		IOMemory::IOMemory()
			:size( 0 )
			,data( 0 )
			,ptr( 0 )
		{
		}

		IOMemory::IOMemory( const char* path, uint8* data, Size size )
			:path( path )
			,size( size )
			,data( data )
			,ptr( data )
		{
		}

		IOMemory::~IOMemory()
		{
		}

		void IOMemory::seekSet( int offset )
		{
			ptr = data + offset;
			if( ptr < data )
			{
				ptr = data;
			}
			else if( ptr > data + size )
			{
				ptr = data + size;
			}
		}

		void IOMemory::seekEnd( int offset )
		{
			ptr = data + size - offset;
			if( ptr < data )
			{
				ptr = data;
			}
			else if( ptr > data + size )
			{
				ptr = data + size;
			}
		}

		void IOMemory::seekCur( int offset )
		{
			ptr += offset;
			if( ptr < data )
			{
				ptr = data;
			}
			else if( ptr > data + size )
			{
				ptr = data + size;
			}
		}

		Size IOMemory::tell() const
		{
			assert( ptr >= data && ptr <= data + size );
			return static_cast<Size>( ptr - data );
		}

		boolean IOMemory::eof() const
		{
			return static_cast<Size>( ptr - data ) >= size;
		}

		Size IOMemory::read( uint8* buffer, Size readSize )
		{
			Size left = data + size - ptr;
			if( readSize > left )
			{
				readSize = left;
			}

			memcpy( buffer, ptr, readSize );
			ptr += readSize;
			return readSize;
		}

		Size IOMemory::write( uint8* buffer, Size writeSize )
		{
			Size left = data + size - ptr;
			if( writeSize > size )
			{
				writeSize = left;
			}

			memcpy( ptr, buffer, writeSize );
			ptr += writeSize;
			return writeSize;
		}

		// IOMap
#ifdef VRLAB_WINDOWS_DESKTOP
		IOMap::IOMap()
			:file( 0 )
			,map( 0 )
		{
		}

		boolean IOMap::createFileMapping()
		{
			file = CreateFileA( path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0 );
			if( file == INVALID_HANDLE_VALUE )
			{
				return false;
			}

			size = GetFileSize( file, 0 );
			if( size == INVALID_FILE_SIZE )
			{
				CloseHandle( file );
				file = 0;
				return false;
			}

			map = CreateFileMapping( file, 0, PAGE_READONLY, 0, 0, 0 );
			if( map == INVALID_HANDLE_VALUE )
			{
				CloseHandle( file );
				file = 0;
				return false;
			}

			data = static_cast<uint8*>( MapViewOfFile( map, FILE_MAP_READ, 0, 0, 0 ) );
			if( data == 0 )
			{
				CloseHandle( map );
				map = 0;
				CloseHandle( file );
				file = 0;
			}

			return true;
		}

		void IOMap::destroyFileMapping()
		{
			if( map )
			{
				CloseHandle( map );
				map = 0;
			}

			if( file )
			{
				CloseHandle( file );
				file = 0;
			}
		}

		IOMap::IOMap( const char* path )
		{
			if( !createFileMapping() )
			{
				assert( 0 );
			}
		}

		IOMap::~IOMap()
		{
			destroyFileMapping();
		}
#endif
	}
}