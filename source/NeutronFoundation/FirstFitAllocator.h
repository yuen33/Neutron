#pragma once

#include "HeapAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		class FirstFitAllocator : public HeapAllocator
		{
		public:
			FirstFitAllocator();
			virtual ~FirstFitAllocator();

			virtual void* allocate( Size size, Size align = 4 );
		};
	}
}