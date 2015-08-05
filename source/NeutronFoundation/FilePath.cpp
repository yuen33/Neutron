#include "FilePath.h"
#include "String.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace Utility
	{
		FilePath::FilePath()
		{
		}

		FilePath::~FilePath()
		{
		}

		String FilePath::regularSlashes( const char* path )
		{
			String line( path );
			return line.replace( "\\", "/" );
		}

		String FilePath::getName( const char* path )
		{
			String line( path );
			line.replace( "\\", "/" );
			int dotIndex = line.rfind( '.' );
			int lastSlashIndex = line.rfind( '/' );

			if( dotIndex >= 0 )
			{
				if( dotIndex >= lastSlashIndex )
				{
					return line.subString( lastSlashIndex + 1, line.getCount() - lastSlashIndex );
				}
			}

			return 0;
		}

		String FilePath::getNameWithoutExt( const char* path )
		{
			String line( path );
			line.replace( "\\", "/" );
			int dotIndex = line.rfind( '.' );
			int lastSlashIndex = line.rfind( '/' );

			if( dotIndex >= 0 )
			{
				if( dotIndex >= lastSlashIndex )
				{
					return line.subString( lastSlashIndex + 1, dotIndex - lastSlashIndex - 1 );
				}
			}

			return 0;
		}

		String FilePath::getExt( const char* path )
		{
			String line( path );
			line.replace( "\\", "/" );
			int dotIndex = line.rfind( '.' );

			if( dotIndex >= 0 )
			{
				if( dotIndex )
				{
					return line.subString( dotIndex + 1, line.getCount() - dotIndex - 1 );
				}
			}

			return 0;
		}

		String FilePath::getPath( const char* path )
		{
			String line( path );
			line.replace( "\\", "/" );
			int lastSlashIndex = line.rfind( '/' );

			if( lastSlashIndex >= 0 )
			{
				return line.subString( 0, lastSlashIndex );
			}

			return 0;
		}
	}
}