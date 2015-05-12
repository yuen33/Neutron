#pragma once

#include "HeapAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		class WorstFitAllocator : public HeapAllocator
		{
		public:
			WorstFitAllocator();
			virtual ~WorstFitAllocator();

			void* allocate( Size size, Size align = 4 );
		};
	}
}