#include "SystemAllocator.h"
#include "ChunkedAllocator.h"
#include "FirstFitAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		SystemAllocator::SystemAllocator()
			:parentAllocator( 0 )
			,chunkedAllocatorCount( 0 )
			,chunkedAllocators( 0 )
			,lastAllocatedChunkedAllocator( 0 )
			,lastDeallocatedChunkedAllocator( 0 )
			,smallHeapAllocator( 0 )
			,mediumHeapAllocator( 0 )
			,largeHeapAllocator( 0 )
		{
		}

		SystemAllocator::~SystemAllocator()
		{
		}

		bool SystemAllocator::init( Size capacity, Allocator* parentAllocator )
		{
			assert( parentAllocator );
			this->parentAllocator = parentAllocator;
			for( Size i = 4; i <= CHUNKED_SIZE; i <<= 1 )
			{
				++chunkedAllocatorCount;
			}

			chunkedAllocators = static_cast<ChunkedAllocator*>( parentAllocator->allocate( sizeof( ChunkedAllocator ) * chunkedAllocatorCount ) );
			assert( chunkedAllocators );


			bool ret = true;
			Size blockSize = 4;
			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				chunkedAllocators[i] = *( new( &chunkedAllocators[i] )ChunkedAllocator );
				ret = ret && chunkedAllocators[i].init( blockSize << i, parentAllocator );
			}

			smallHeapAllocator = new ( static_cast<FirstFitAllocator*>( parentAllocator->allocate( sizeof( FirstFitAllocator ) ) ) )FirstFitAllocator;
			ret = ret && smallHeapAllocator->init( SMALL_HEAP_SIZE, parentAllocator );
			mediumHeapAllocator = new ( static_cast<FirstFitAllocator*>( parentAllocator->allocate( sizeof( FirstFitAllocator ) ) ) )FirstFitAllocator;
			ret = ret && mediumHeapAllocator->init( MEDIUM_HEAP_SIZE, parentAllocator );
			largeHeapAllocator = new ( static_cast<FirstFitAllocator*>( parentAllocator->allocate( sizeof( FirstFitAllocator ) ) ) )FirstFitAllocator;
			ret = ret && largeHeapAllocator->init( LARGE_HEAP_SIZE, parentAllocator );

			if( !ret )
			{
				release();
			}

			return ret;
		}

		void SystemAllocator::release()
		{
#ifdef NEUTRON_DEBUG
			// check memory leak
			if( getTotalAllocatedSize() != 0 )
			{
				printStats();
				if( largeHeapAllocator->getTotalAllocatedSize() != 0 )
				{
					printf( "Memory leak at large heap allocator: %u\n", largeHeapAllocator->getTotalAllocatedSize() );
				}
				if( mediumHeapAllocator->getTotalAllocatedSize() != 0 )
				{
					printf( "Memory leak at large heap allocator: %u\n", mediumHeapAllocator->getTotalAllocatedSize() );
				}
				if( smallHeapAllocator->getTotalAllocatedSize() != 0 )
				{
					printf( "Memory leak at large heap allocator: %u\n", smallHeapAllocator->getTotalAllocatedSize() );
				}

				for( int i = 0; i < chunkedAllocatorCount; ++i )
				{
					if( chunkedAllocators[i].getTotalAllocatedSize() != 0 )
					{
						printf( "Memory leak at Chunked allocator ( block size %u bytes ): %u\n", 4 << i, chunkedAllocators[i].getTotalAllocatedSize() );
					}
				}

				assert( 0 );
			}
#endif

			if( largeHeapAllocator )
			{
				largeHeapAllocator->release();
				largeHeapAllocator->~FirstFitAllocator();
				parentAllocator->deallocate( largeHeapAllocator );
				largeHeapAllocator = 0;
			}
			if( mediumHeapAllocator )
			{
				mediumHeapAllocator->release();
				mediumHeapAllocator->~FirstFitAllocator();
				parentAllocator->deallocate( mediumHeapAllocator );
				mediumHeapAllocator = 0;
			}
			if( smallHeapAllocator )
			{
				smallHeapAllocator->release();
				smallHeapAllocator->~FirstFitAllocator();
				parentAllocator->deallocate( smallHeapAllocator );
				smallHeapAllocator = 0;
			}

			lastAllocatedChunkedAllocator = 0;
			lastDeallocatedChunkedAllocator = 0;
			
			if( chunkedAllocatorCount > 0 )
			{
				for( int i = 0; i < chunkedAllocatorCount; ++i )
				{
					chunkedAllocators[i].release();
					chunkedAllocators[i].~ChunkedAllocator();
				}

				parentAllocator->deallocate( chunkedAllocators );
				chunkedAllocators = 0;
			}

			chunkedAllocatorCount = 0;
			parentAllocator = 0;
		}

		void* SystemAllocator::allocate( Size size, Size align )
		{
			if( size == 0 )
			{
				return 0;
			}
			else if( size <= CHUNKED_SIZE )
			{
				Size lastBlockSize = 0;
				if( !lastAllocatedChunkedAllocator || size > lastAllocatedChunkedAllocator->getBlockSize() || size <= lastAllocatedChunkedAllocator->getBlockSize() >> 1 )
				{
					for( int i = 0; i < chunkedAllocatorCount; ++i )
					{
						if( size <= chunkedAllocators[i].getBlockSize() )
						{
							lastAllocatedChunkedAllocator = &chunkedAllocators[i];
							break;
						}
					}
				}

				return lastAllocatedChunkedAllocator->allocate( size, align );
			}
			else if( size <= SMALL_SIZE )
			{
				return smallHeapAllocator->allocate( size, align );
			}
			else if( size <= MEDIUM_SIZE )
			{
				return mediumHeapAllocator->allocate( size, align );
			}
			else if( size <= LARGE_SIZE )
			{
				return largeHeapAllocator->allocate( size, align );
			}

			return parentAllocator->allocate( size, align );
		}

		void* SystemAllocator::reallocate( void* p, Size size, Size align )
		{
			if( lastAllocatedChunkedAllocator && lastDeallocatedChunkedAllocator->allocated( p ) )
			{
				Size dataSize = lastAllocatedChunkedAllocator->getDataSize( p );
				void* newPtr = allocate( size, align );
				assert( newPtr );
				memcpy( newPtr, p, dataSize );
				lastDeallocatedChunkedAllocator->deallocate( p );
				return newPtr;
			}

			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				if( chunkedAllocators[i].allocated( p ) )
				{
					lastDeallocatedChunkedAllocator = &chunkedAllocators[i];
					Size dataSize = lastDeallocatedChunkedAllocator->getDataSize( p );
					void* newPtr = allocate( size, align );
					assert( newPtr );
					memcpy( newPtr, p, dataSize );
					lastDeallocatedChunkedAllocator->deallocate( p );
					return newPtr;
				}
			}

			if( smallHeapAllocator->allocated( p ) )
			{
				Size dataSize = smallHeapAllocator->getDataSize( p );
				void* newPtr = allocate( size, align );
				assert( newPtr );
				memcpy( newPtr, p, dataSize );
				smallHeapAllocator->deallocate( p );
				return newPtr;
			}

			if( mediumHeapAllocator->allocated( p ) )
			{
				Size dataSize = mediumHeapAllocator->getDataSize( p );
				void* newPtr = allocate( size, align );
				assert( newPtr );
				memcpy( newPtr, p, dataSize );
				mediumHeapAllocator->deallocate( p );
				return newPtr;
			}

			if( largeHeapAllocator->allocated( p ) )
			{
				Size dataSize = largeHeapAllocator->getDataSize( p );
				void* newPtr = allocate( size, align );
				assert( newPtr );
				memcpy( newPtr, p, dataSize );
				largeHeapAllocator->deallocate( p );
				return newPtr;
			}

			return parentAllocator->reallocate( p, size, align );
		}

		void SystemAllocator::deallocate( void* p )
		{
			if( p )
			{
				if( lastDeallocatedChunkedAllocator && lastDeallocatedChunkedAllocator->allocated( p ) )
				{
					lastDeallocatedChunkedAllocator->deallocate( p );
					return;
				}

				for( int i = 0; i < chunkedAllocatorCount; ++i )
				{
					if( chunkedAllocators[i].allocated( p ) )
					{
						lastDeallocatedChunkedAllocator = &chunkedAllocators[i];
						lastDeallocatedChunkedAllocator->deallocate( p );
						return;
					}
				}

				if( smallHeapAllocator->allocated( p ) )
				{
					smallHeapAllocator->deallocate( p );
					return;
				}
				if( mediumHeapAllocator->allocated( p ) )
				{
					mediumHeapAllocator->deallocate( p );
					return;
				}
				if( largeHeapAllocator->allocated( p ) )
				{
					largeHeapAllocator->deallocate( p );
					return;
				}

				parentAllocator->deallocate( p );
			}
		}

		boolean SystemAllocator::allocated( void* p )
		{
			if( lastDeallocatedChunkedAllocator && lastDeallocatedChunkedAllocator->allocated( p ) )
			{
				return true;
			}

			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				if( chunkedAllocators[i].allocated( p ) )
				{
					lastDeallocatedChunkedAllocator = &chunkedAllocators[i];
					return true;
				}
			}

			if( smallHeapAllocator->allocated( p ) )
			{
				return true;
			}
			if( mediumHeapAllocator->allocated( p ) )
			{
				return true;
			}
			if( largeHeapAllocator->allocated( p ) )
			{
				return true;
			}

			return false;
		}

		Size SystemAllocator::getDataSize( void* p )
		{
			if( lastDeallocatedChunkedAllocator && lastDeallocatedChunkedAllocator->allocated( p ) )
			{
				return lastDeallocatedChunkedAllocator->getDataSize( p );
			}

			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				if( chunkedAllocators[i].allocated( p ) )
				{
					lastDeallocatedChunkedAllocator = &chunkedAllocators[i];
					return lastDeallocatedChunkedAllocator->getDataSize( p );
				}
			}

			if( smallHeapAllocator->allocated( p ) )
			{
				return smallHeapAllocator->getDataSize( p );
			}
			if( mediumHeapAllocator->allocated( p ) )
			{
				return mediumHeapAllocator->getDataSize( p );
			}
			if( largeHeapAllocator->allocated( p ) )
			{
				return largeHeapAllocator->getDataSize( p );
			}

			return SIZE_NOT_TRACKED;
		}

		Size SystemAllocator::getCapacity() const
		{
			Size capacity = 0;
			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				capacity += chunkedAllocators[i].getCapacity();
			}

			capacity += smallHeapAllocator->getCapacity();
			capacity += mediumHeapAllocator->getCapacity();
			capacity += largeHeapAllocator->getCapacity();

			return capacity;
		}

		Size SystemAllocator::getTotalAllocatedSize() const
		{
			Size size = 0;
			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				size += chunkedAllocators[i].getTotalAllocatedSize();
			}

			size += smallHeapAllocator->getTotalAllocatedSize();
			size += mediumHeapAllocator->getTotalAllocatedSize();
			size += largeHeapAllocator->getTotalAllocatedSize();
			
			return size;
		}

		int SystemAllocator::getTotalAllocationCount() const
		{
			int count = 0;
			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				count += chunkedAllocators[i].getTotalAllocationCount();
			}

			count += smallHeapAllocator->getTotalAllocationCount();
			count += mediumHeapAllocator->getTotalAllocationCount();
			count += largeHeapAllocator->getTotalAllocationCount();
			
			return count;
		}

		void SystemAllocator::printStats()
		{
			printf( "Total %d chunked allocators: \n", chunkedAllocatorCount );
			for( int i = 0; i < chunkedAllocatorCount; ++i )
			{
				printf( "%u byte chunked allocator: \n", 4 << i );
				chunkedAllocators[i].printStats();
				printf( "\n" );
			}
			printf( "--------------------------------------------------------\n" );

			printf( "Small heap allocator: \n" );
			smallHeapAllocator->printStats();
			printf( "--------------------------------------------------------\n" );

			printf( "Medium heap allocator: \n" );
			mediumHeapAllocator->printStats();
			printf( "--------------------------------------------------------\n" );

			printf( "Large heap allocator: \n" );
			largeHeapAllocator->printStats();
			printf( "--------------------------------------------------------\n" );
		}
	}
}