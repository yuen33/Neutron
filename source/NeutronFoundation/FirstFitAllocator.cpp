#include "FirstFitAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		FirstFitAllocator::FirstFitAllocator()
		{
		}

		FirstFitAllocator::~FirstFitAllocator()
		{
		}

		void* FirstFitAllocator::allocate( Size size, Size align )
		{
			if( free && free->available( size, align ) )
			{
				HeapMemoryItem* newItem = split( free, size, align );
				if( newItem )
				{
					allocatedSize += newItem->allocatedSize();
					fragmentSize += newItem->fragmentSize();
					++allocationCount;

					if( free == newItem )
					{
						free = 0;
					}

					return newItem->data();
				}
			}
			else
			{
				HeapMemoryItem* item = 0;
				for( item = static_cast<HeapMemoryItem*>( freeList.getFront() ); item; item = static_cast<HeapMemoryItem*>( item->getNext() ) )
				{
					if( item->available( size, align ) )
					{
						break;
					}
				}

				if( item )
				{
					HeapMemoryItem* newItem = split( item, size, align );
					if( newItem )
					{
						free = ( item != newItem ) ? item : 0;
					}
					return newItem->data();
				}
			}

			return 0;
		}
	}
}