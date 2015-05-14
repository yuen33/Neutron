#include "Timer.h"

namespace Neutron
{
	namespace Utility
	{
#ifdef NEUTRON_WINDOWS
		int64 Timer::frequency = -1;

		Timer::Timer()
		{
			if( frequency < 0 )
			{
				LARGE_INTEGER freq = { 0 };
				QueryPerformanceFrequency( &freq );
				frequency = freq.QuadPart;
			}

			start = now();
		}

		Timer::~Timer()
		{
		}

		uint64 Timer::getTimeUS( int64 raw )
		{
			int64 quotient = raw / frequency;
			int64 remainder = raw % frequency;
			return static_cast< uint64 >( quotient )* 1000000ULL + static_cast< uint64 >( remainder * 1000000 / static_cast< uint64 >( frequency ) );
		}
#endif
	}
}