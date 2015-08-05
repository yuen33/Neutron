#pragma once

#include "NeutronFoundationCommon.h"
#include "String.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE FilePath
		{
		public:
			FilePath();
			virtual ~FilePath();
			
			static String regularSlashes( const char* path );
			static String getName( const char* path );
			static String getNameWithoutExt( const char* path );
			static String getExt( const char* path );
			static String getPath( const char* path );
		};
	}
}