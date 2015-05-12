#pragma once

#include "HeapAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		class BestFitAllocator : public HeapAllocator
		{
		public:
			BestFitAllocator();
			virtual ~BestFitAllocator();

			virtual void* allocate( Size size, Size align = 4 );
		};
	}
}