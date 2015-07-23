#pragma once

#include "NeutronSystemCommon.h"

namespace Neutron
{
	namespace System
	{
		namespace Log
		{
#ifdef NEUTRON_WINDOWS_DESKTOP
			enum : uint32
			{
				DefaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
				MessageColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
				WarningColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
				ErrorColor = FOREGROUND_RED | FOREGROUND_INTENSITY,
				DebugColor = FOREGROUND_GREEN | FOREGROUND_BLUE
			};
#endif

			NEUTRON_CORE inline void message( const char* sender, const char* fmt, ... );
			NEUTRON_CORE inline void warning( const char* sender, const char* fmt, ... );
			NEUTRON_CORE inline void error( const char* sender, const char* fmt, ... );
			NEUTRON_CORE inline void debug( const char* fmt, ... );
		}
	}
}