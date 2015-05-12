#include "WorstFitAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		WorstFitAllocator::WorstFitAllocator()
		{
		}

		WorstFitAllocator::~WorstFitAllocator()
		{
		}

		void* WorstFitAllocator::allocate( Size size, Size align )
		{
			HeapMemoryItem* worstItem = 0;
			for( HeapMemoryItem* item = static_cast<HeapMemoryItem*>( freeList.getFront() ); item; item = static_cast<HeapMemoryItem*>( item->getNext() ) )
			{
				if( item->free() && ( !worstItem || item->dataSize() > worstItem->dataSize() ) )
				{
					worstItem = item;
				}
			}

			if( worstItem && worstItem->available( size, align ) )
			{
				HeapMemoryItem* newItem = split( worstItem, size, align );
				if( newItem )
				{
					allocatedSize += newItem->allocatedSize();
					fragmentSize += newItem->fragmentSize();
					++allocationCount;
					return newItem->data();
				}
			}

			return 0;
		}
	}
}