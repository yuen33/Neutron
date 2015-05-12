#include "HeapAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		// HeapMemoryItem
		HeapMemoryItem::HeapMemoryItem()
			:flag( 0 )
		{
		}

		HeapMemoryItem::HeapMemoryItem( void* data, Size size, HeapMemoryItem* prev, HeapMemoryItem* next )
			:flag( 0 )
		{
			setPrev( prev );
			setNext( next );
		}

		HeapMemoryItem::~HeapMemoryItem()
		{
		}

		boolean HeapMemoryItem::available( Size size, Size align )
		{
			if( free() )
			{
				uint8* start = data();
				if( alignForward( start, align ) != start )
				{
					size += sizeof( HeapMemoryItem ) + align - 1;
				}
				return size < dataSize();
			}

			return false;
		}

		// HeapAllocator
		HeapAllocator::HeapAllocator()
			:parentAllocator( 0 )
			,capacity( 0 )
			,data( 0 )
			,allocatedSize( 0 )
			,fragmentSize( 0 )
			,allocationCount( 0 )
		{
		}

		HeapAllocator::~HeapAllocator()
		{
		}

		boolean HeapAllocator::init( Size capacity, Allocator* parentAllocator )
		{
			if( !parentAllocator )
			{
				return false;
			}

			this->capacity = capacity;
			this->parentAllocator = parentAllocator;

			data = static_cast<uint8*>( parentAllocator->allocate( capacity ) );
			assert( data );

			HeapMemoryItem* first = reinterpret_cast<HeapMemoryItem*>( data );
			HeapMemoryItem* free = first + 1;
			HeapMemoryItem* last = reinterpret_cast<HeapMemoryItem*>( data + capacity ) - 1;

			first->setUsed();
			free->setFree();
			last->setUsed();

			freeList.pushBack( first );
			freeList.pushBack( free );
			freeList.pushBack( last );			

			this->free = free;
			allocatedSize = 0;
			fragmentSize = 0;
			allocationCount = 0;

			return true;
		}

		void HeapAllocator::release()
		{
			// check memory leak
			assert( allocatedSize == 0 );

			allocationCount = 0;
			allocatedSize = 0;
			free = 0;

			freeList.clear();

			parentAllocator->deallocate( data );
			data = 0;
			capacity = 0;
		}

		void* HeapAllocator::reallocate( void* p, Size size, Size align )
		{
			if( allocated( p ) )
			{
				void* newPtr = allocate( size, align );
				if( newPtr )
				{
					Size oldSize = poinerToItem( p )->dataSize();
					memcpy( newPtr, p, oldSize );
					deallocate( p );

					return newPtr;
				}
			}
			return 0;
		}

		void HeapAllocator::deallocate( void* p )
		{
			if( p && allocated( p ) )
			{
				HeapMemoryItem* item = poinerToItem( p );
				allocatedSize -= item->allocatedSize();
				fragmentSize -= item->fragmentSize();
				merge( item );
			}
		}

		boolean HeapAllocator::allocated( void* p )
		{
			uint8* pt = reinterpret_cast<uint8*>( p );
			return ( pt > data && pt < data + capacity );
		}

		Size HeapAllocator::getDataSize( void* p )
		{
			assert( allocated( p ) );
			return poinerToItem( p )->dataSize();
		}

		HeapMemoryItem* HeapAllocator::poinerToItem( void* p )
		{
			return reinterpret_cast<HeapMemoryItem*>( p ) - 1;
		}

		HeapMemoryItem* HeapAllocator::split( HeapMemoryItem* item, Size size, Size align )
		{
			uint8* start = item->data() + item->dataSize();
			start -= size;
			Size alignment = reinterpret_cast<uint8*>( alignForward( start, align ) ) - start;
			size += alignment;
			start -= alignment;
			start -= sizeof( HeapMemoryItem );

			if( start <= item->data() )
			{
				// heap full
				return 0;
			}

			HeapMemoryItem* newItem = reinterpret_cast<HeapMemoryItem*>( start );
			newItem->setFree();
			freeList.insertAfter( newItem, item );
			newItem->setUsed();
			return newItem;
		}

		void HeapAllocator::merge( HeapMemoryItem* item )
		{
			HeapMemoryItem* nextItem = static_cast<HeapMemoryItem*>( item->getNext() );
			if( nextItem && nextItem->free() )
			{
				if( free == nextItem )
				{
					free = item;
				}

				freeList.remove( nextItem );
			}

			HeapMemoryItem* prevItem = static_cast<HeapMemoryItem*>( item->getPrev() );
			if( prevItem && prevItem->free() )
			{
				if( free == item )
				{
					free = prevItem;
				}

				freeList.remove( item );
			}
		}

		void HeapAllocator::printStats()
		{
			printf( "Total allocated size = %u, allocation = %d, fragment = %u, boundary from %p to %p size = %u\n", allocatedSize, allocationCount, fragmentSize, data, data + capacity, capacity );
		}
	}
}