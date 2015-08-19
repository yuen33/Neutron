#pragma once

#include "PixelFormat.h"
#include "NeutronFoundation/CompileHash.h"
#include "NeutronFoundation/String.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			// access hint
			enum : int
			{
				AH_Unknown = 0,
				AH_CPU_Read = 1 << 0,
				AH_CPU_Write = 1 << 1,
				AH_GPU_Read = 1 << 2,
				AH_GPU_Write = 1 << 3,
				AH_GPU_Unordered = 1 << 4,
				AH_GenerateMips = 1 << 5,
				AH_Immutable = 1 << 6,
				AH_Raw = 1 << 7,
				AH_Append = 1 << 8,
				AH_Counter = 1 << 9,
				AH_DrawInDirectArgs = 1 << 10
			};

			static int ParseAccessHint( const char* line )
			{
				if( line == 0 || line[0] == '\0' )
				{
					return 0;
				}

				int ret = 0;
				String str( line );
				if( str.find( "CPU_Read" ) >= 0 )
				{
					ret |= AH_CPU_Read;
				}
				if( str.find( "CPU_Write" ) >= 0 )
				{
					ret |= AH_CPU_Write;
				}
				if( str.find( "GPU_Read" ) >= 0 )
				{
					ret |= AH_GPU_Read;
				}
				if( str.find( "GPU_Write" ) >= 0 )
				{
					ret |= AH_GPU_Write;
				}
				if( str.find( "GPU_Unordered" ) >= 0 )
				{
					ret |= AH_GPU_Unordered;
				}
				if( str.find( "GenerateMips" ) >= 0 )
				{
					ret |= AH_GenerateMips;
				}
				if( str.find( "Immutable" ) >= 0 )
				{
					ret |= AH_Immutable;
				}
				if( str.find( "Raw" ) >= 0 )
				{
					ret |= AH_Raw;
				}
				if( str.find( "Append" ) >= 0 )
				{
					ret |= AH_Append;
				}
				if( str.find( "Counter" ) >= 0 )
				{
					ret |= AH_Counter;
				}
				if( str.find( "DrawInDirectArgs" ) >= 0 )
				{
					ret |= AH_DrawInDirectArgs;
				}

				return ret;
			}
		}
	}
}