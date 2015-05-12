#pragma once

#include "Allocator.h"

namespace Neutron
{
	namespace Memory
	{
		class MemoryChunk
		{
			friend class ChunkedAllocator;

			Allocator*		parentAllocator;
			int				allocationCount;
			Size			blockSize;

			uint8*			data;
			uint8*			dataBegin;
			uint8*			dataEnd;

			uint8			firstBlock;
			uint8			freeBlocks;
			uint8			blockCount;

		public:
			MemoryChunk();
			virtual ~MemoryChunk();

			boolean init( Allocator* parentAllocator, Size blockSize, int blockCapacity );
			void release();
			inline boolean free() const { return freeBlocks == blockCount; }
			inline boolean allocated( void* p ) const { return p >= dataBegin && p < dataEnd; }
			void* allocate();
			void deallocate( void* p );

			void printStats();
		};

		class ChunkedAllocator : public Allocator
		{
			static const uint8 blockPerChunk = 0xFF;
			Allocator*		parentAllocator;
			Size			blockSize;
			int				chunkCount;
			int				chunkCapacity;

			MemoryChunk*	chunks;
			MemoryChunk*	lastAllocatedChunk;
			MemoryChunk*	lastDeallocatedChunk;

			Size			allocatedSize;
			int				allocationCount;
			int				findChunk( void* p ) const;

		public:
			ChunkedAllocator();
			virtual ~ChunkedAllocator();

			virtual boolean init( Size blockSize, Allocator* parentAllocator );
			virtual void release();
			virtual void* allocate( Size size, Size align = 4 );
			inline virtual void* reallocate( void* p, Size size, Size align = 4 ) { return 0; }
			virtual void deallocate( void* p );

			virtual boolean allocated( void* p );
			inline virtual Size getDataSize( void* p );
			Size getCapacity() const;
			inline virtual Size getTotalAllocatedSize() const { return allocatedSize; }
			inline virtual int getTotalAllocationCount() const { return allocationCount; }
			inline virtual Size getBlockSize() const { return blockSize; }

			void printStats();
		};
	}
}