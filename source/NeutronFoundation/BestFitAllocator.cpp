#include "BestFitAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		BestFitAllocator::BestFitAllocator()
		{
		}

		BestFitAllocator::~BestFitAllocator()
		{
		}

		void* BestFitAllocator::allocate( Size size, Size align )
		{
			HeapMemoryItem* bestItem = 0;
			for( HeapMemoryItem* item = static_cast<HeapMemoryItem*>( freeList.getFront() ); item; item = static_cast<HeapMemoryItem*>( item->getNext() ) )
			{
				if( ( !bestItem || item->dataSize() < bestItem->dataSize() ) && item->available( size, align ) )
				{
					if( item->dataSize() == size )
					{
						item->setUsed();
						allocatedSize += item->allocatedSize();
						fragmentSize += item->fragmentSize();
						++allocationCount;
						return item->data();
					}
					bestItem = item;
				}
			}

			if( bestItem )
			{
				HeapMemoryItem* newItem = split( bestItem, size, align );
				if( newItem )
				{
					allocatedSize = newItem->allocatedSize();
					fragmentSize += newItem->fragmentSize();
					++allocationCount;
					return newItem->data();
				}
			}

			return 0;
		}
	}
}