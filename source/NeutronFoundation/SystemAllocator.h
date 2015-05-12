#pragma once

#include "Allocator.h"

namespace Neutron
{
	namespace Memory
	{
		class ChunkedAllocator;
		class FirstFitAllocator;

		class NEUTRON_FOUNDATION_CORE SystemAllocator : public Allocator
		{
			enum
			{
				CHUNKED_SIZE = 128,
				SMALL_SIZE = 1024,
				SMALL_HEAP_SIZE = 1024 * 1024 * 4,
				MEDIUM_SIZE = 1024 * 16,
				MEDIUM_HEAP_SIZE = 1024 * 1024 * 8,
				LARGE_SIZE = 1024 * 256,
				LARGE_HEAP_SIZE = 1024 * 1024 * 16
			};

			Allocator*			parentAllocator;

			int					chunkedAllocatorCount;
			ChunkedAllocator*	chunkedAllocators;
			ChunkedAllocator*	lastAllocatedChunkedAllocator;
			ChunkedAllocator*	lastDeallocatedChunkedAllocator;

			FirstFitAllocator*	smallHeapAllocator;
			FirstFitAllocator*	mediumHeapAllocator;
			FirstFitAllocator*	largeHeapAllocator;

		public:
			SystemAllocator();
			virtual ~SystemAllocator();

			virtual bool init( Size capacity, Allocator* parentAllocator );
			virtual void release();
			virtual void* allocate( Size size, Size align = 4 );
			virtual void* reallocate( void* p, Size size, Size align = 4 );
			virtual void deallocate( void* p );

			virtual boolean allocated( void* p );
			virtual Size getDataSize( void* p );
			virtual Size getCapacity() const;
			virtual Size getTotalAllocatedSize() const;
			virtual int getTotalAllocationCount() const;

			void printStats();
		};
	}
}