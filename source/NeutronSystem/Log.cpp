#include "Log.h"

namespace Neutron
{
	namespace System
	{
		namespace Log
		{
#ifdef NEUTRON_WINDOWS_DESKTOP
			void setStdConsoleColor( uint32 color )
			{
				HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
				SetConsoleTextAttribute( h, color );
			}
#endif

			void message( const char* sender, const char* fmt, ... )
			{
				assert( sender && fmt );
				setStdConsoleColor( MessageColor );
				printf( "[%s] ", sender );
				va_list arg_list = 0;
				vprintf( fmt, arg_list );
				va_end( arg_list );
				setStdConsoleColor( DefaultColor );
			}

			void warning( const char* sender, const char* fmt, ... )
			{
				assert( sender && fmt );
				setStdConsoleColor( WarningColor );
				printf( "[%s] ", sender );
				va_list arg_list = 0;
				vprintf( fmt, arg_list );
				va_end( arg_list );
				setStdConsoleColor( DefaultColor );
			}

			void error( const char* sender, const char* fmt, ... )
			{
				assert( sender && fmt );
				setStdConsoleColor( ErrorColor );
				printf( "[%s] ", sender );
				va_list arg_list = 0;
				vprintf( fmt, arg_list );
				va_end( arg_list );
				setStdConsoleColor( DefaultColor );
			}

#ifdef NEUTRON_DEBUG
			void debug( const char* fmt, ... )
			{
				assert( fmt );
				setStdConsoleColor( DebugColor );
				va_list arg_list = 0;
				va_start( arg_list, fmt );
				vprintf( fmt, arg_list );
				va_end( arg_list );
				setStdConsoleColor( DefaultColor );
			}
#else
			void debug()
			{
			}
#endif
		}
	}
}