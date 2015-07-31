#pragma once

#include "NeutronFoundationCommon.h"

namespace Neutron
{
	namespace Utility
	{
#ifdef NEUTRON_WINDOWS
		class NEUTRON_FOUNDATION_CORE Timer
		{
			int64			start;
			static int64	frequency;

			static uint64 getTimeUS( int64 raw );

		public:
			Timer();
			~Timer();

			static inline int64 now()
			{
				LARGE_INTEGER counter = { 0 };
				QueryPerformanceCounter( &counter );
				return counter.QuadPart;
			}

			inline void reset() { start = now(); }
			static inline uint64 timeUS() { return getTimeUS( now() ); }
			static inline uint32 timeMS() { return static_cast<uint32>( timeUS() / 1000ULL ); }
			inline uint64 elapsedUS() { return getTimeUS( now() - start ); }
			inline uint32 elapsedMS() { return static_cast<uint32>( elapsedUS() / 1000ULL ); }
		};
#endif
	}
}