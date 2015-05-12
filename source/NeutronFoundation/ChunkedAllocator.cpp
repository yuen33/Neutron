#include "ChunkedAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		MemoryChunk::MemoryChunk()
			:parentAllocator(0)
			, allocationCount(0)
			, blockSize(0)
			, data(0)
			, dataBegin(0)
			, dataEnd(0)
			, firstBlock(0)
			, freeBlocks(0)
			, blockCount(0)
		{
		}

		MemoryChunk::~MemoryChunk()
		{
		}

		boolean MemoryChunk::init(Allocator* parentAllocator, Size blockSize, int blockCount)
		{
			assert(parentAllocator && blockSize && blockCount > 0);
			this->parentAllocator = parentAllocator;
			this->blockSize = blockSize;
			this->blockCount = blockCount;

			data = static_cast<uint8*>(parentAllocator->allocate(blockSize * blockCount + 16));
			assert(data);
			dataBegin = static_cast<uint8*>(alignForward(data, 16));
			dataEnd = dataBegin + blockSize * blockCount;
			firstBlock = 0;
			freeBlocks = blockCount;
			uint8* p = dataBegin;
			for (uint8 i = 1; i < blockCount; ++i, p += blockSize)
			{
				*p = i;
			}
			return true;
		}

		void MemoryChunk::release()
		{
			assert(free());
			parentAllocator->deallocate(data);
			data = 0;
			dataBegin = 0;
			dataEnd = 0;
			firstBlock = 0;
			freeBlocks = 0;
		}

		void* MemoryChunk::allocate()
		{
			assert(freeBlocks > 0);
			uint8* ret = dataBegin + firstBlock * blockSize;
			firstBlock = *ret;
			--freeBlocks;
			++allocationCount;
			return ret;
		}

		void MemoryChunk::deallocate(void* p)
		{
			if (p && allocated(p))
			{
				uint8* ptr = static_cast<uint8*>(p);
				// check bad pointer
				assert((static_cast<uint8*>(p)-dataBegin) % blockSize == 0);
				*ptr = firstBlock;
				firstBlock = static_cast<uint8>((ptr - dataBegin) / blockSize);
				++freeBlocks;
			}
		}

		void MemoryChunk::printStats()
		{
			printf("block size = %u, total allocated size = %u, allocation = %d, boundary from %p to %p size = %u\n", blockSize, (blockCount - freeBlocks) * blockSize, allocationCount, data, data + blockSize * blockCount + 16, blockSize * blockCount + 16);
		}

		// ChunkedAllocator
		ChunkedAllocator::ChunkedAllocator()
			:parentAllocator(0)
			, blockSize(0)
			, chunkCount(0)
			, chunkCapacity(0)
			, chunks(0)
			, lastAllocatedChunk(0)
			, lastDeallocatedChunk(0)
			, allocatedSize(0)
			, allocationCount(0)
		{
		}

		ChunkedAllocator::~ChunkedAllocator()
		{
		}

		boolean ChunkedAllocator::init(Size blockSize, Allocator* parentAllocator)
		{
			this->blockSize = blockSize;
			this->parentAllocator = parentAllocator;
			chunkCapacity = 0;
			return true;
		}

		void ChunkedAllocator::release()
		{
			for( int i = 0; i < chunkCount; ++i )
			{
				chunks[i].release();
				chunks[i].~MemoryChunk();
			}

			parentAllocator->deallocate( chunks );
		}

		void* ChunkedAllocator::allocate( Size size, Size align )
		{
			assert( size <= blockSize );
			if( lastAllocatedChunk && lastAllocatedChunk->freeBlocks > 0 )
			{
				allocatedSize += blockSize;
				++allocationCount;
				return lastAllocatedChunk->allocate();
			}

			for( int i = 0; i < chunkCount; ++i )
			{
				if( chunks[i].freeBlocks > 0 )
				{
					lastAllocatedChunk = &chunks[i];
					allocatedSize += blockSize;
					++allocationCount;
					return lastAllocatedChunk->allocate();
				}
			}

			// grow
			if( chunkCount == chunkCapacity )
			{
				chunkCapacity = chunkCapacity + chunkCapacity / 2 + 1;
				chunks = static_cast<MemoryChunk*>( parentAllocator->reallocate( chunks, sizeof( MemoryChunk ) * chunkCapacity, 4 ) );
				assert( chunks );
				lastAllocatedChunk = 0;
				lastDeallocatedChunk = 0;
			}

			MemoryChunk chunk;
			chunk.init( parentAllocator, blockSize, blockPerChunk );
			int index = findChunk( chunk.dataBegin ) + 1;
			for( int i = chunkCount; i > index; i-- )
			{
				chunks[i] = chunks[i-1];
			}
			++chunkCount;
			
			chunks[index] = *( new( &chunks[index] )MemoryChunk );
			chunks[index] = chunk;
			lastAllocatedChunk = &chunks[index];
			allocatedSize += blockSize;
			++allocationCount;
			return lastAllocatedChunk->allocate();
		}

		void ChunkedAllocator::deallocate(void* p)
		{
			if( lastAllocatedChunk && lastAllocatedChunk->allocated( p ) )
			{
				lastDeallocatedChunk = lastAllocatedChunk;
			}
			else if( !lastDeallocatedChunk || !lastDeallocatedChunk->allocated( p ) )
			{
				int index = findChunk( p );
				assert( index < chunkCount );
				lastDeallocatedChunk = &chunks[index];
			}

			allocatedSize -= blockSize;
			lastDeallocatedChunk->deallocate( p );

			if( lastDeallocatedChunk->free() )
			{
				lastDeallocatedChunk->release();
				int index = static_cast<int>( lastDeallocatedChunk - chunks );
				for( int i = index + 1; i < chunkCount; ++i )
				{
					chunks[i-1] = chunks[i];
				}
				--chunkCount;
				lastAllocatedChunk = 0;
				lastDeallocatedChunk = 0;
			}
		}

		boolean ChunkedAllocator::allocated(void* p)
		{
			if( lastAllocatedChunk && lastAllocatedChunk->allocated( p ) ) return true;
			if( lastDeallocatedChunk && lastDeallocatedChunk->allocated( p ) ) return true;

			int index = findChunk( p );
			if( index >= 0 && index < chunkCount && chunks[index].allocated( p ) )
			{
				lastDeallocatedChunk = &chunks[index];
				return true;
			}

			return false;
		}

		Size ChunkedAllocator::getDataSize(void* p)
		{
			assert( allocated( p ) );
			return blockSize;
		}

		Size ChunkedAllocator::getCapacity() const
		{
			return blockSize * blockPerChunk * chunkCount;
		}

		int ChunkedAllocator::findChunk( void* p ) const
		{
			int left = 0;
			int right = chunkCount - 1;
			while( left <= right )
			{
				int middle = ( left + right ) >> 1;
				if( chunks[middle].dataBegin < p ) left = middle + 1;
				else if( chunks[middle].dataBegin > p ) right = middle - 1;
				else return middle;
			}

			return left - 1;
		}

		void ChunkedAllocator::printStats()
		{
			printf( "Total allocated size = %u, alloctions = %u, total %u chunks:\n", allocatedSize, allocationCount, chunkCount );
			for( int i = 0; i < chunkCount; ++i )
			{
				printf( "Chunk #%u ", i );
				chunks[i].printStats();
			}
		}
	}
}