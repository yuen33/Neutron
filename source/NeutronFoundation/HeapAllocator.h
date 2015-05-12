#pragma once

#include "Allocator.h"
#include "MemoryList.h"

namespace Neutron
{
	namespace Memory
	{
		class HeapMemoryItem : public ListItem
		{
		public:
			enum : uint8
			{
				MEM_FLAG_USED = 1 << 0
			};

			uint8 flag;

		public:
			HeapMemoryItem();
			HeapMemoryItem(void* data, Size size, HeapMemoryItem* prev, HeapMemoryItem* next);
			~HeapMemoryItem();

			inline boolean free() const { return flag == 0; }
			inline void setFree() { flag = 0; }
			inline void setUsed() { flag = MEM_FLAG_USED; }
			boolean available(Size size, Size align = 4);
			inline uint8* data() { return reinterpret_cast<uint8*>(this) + sizeof( HeapMemoryItem ); }
			inline Size dataSize() { return allocatedSize() - sizeof( HeapMemoryItem ); }
			inline Size allocatedSize() { return reinterpret_cast<uint8*>( getNext() ) - reinterpret_cast<uint8*>(this); }
			inline Size fragmentSize() { return sizeof( HeapMemoryItem ); }
		};

		class HeapAllocator : public Allocator
		{
		protected:
			Allocator*			parentAllocator;
			Size				capacity;
			uint8*				data;
			List				freeList;

			HeapMemoryItem*		free;
			Size				allocatedSize;
			Size				fragmentSize;
			int					allocationCount;

			HeapMemoryItem* poinerToItem( void* p );
			HeapMemoryItem* split( HeapMemoryItem* item, Size size, Size align = 4 );
			void merge( HeapMemoryItem* item );

		public:
			HeapAllocator();
			virtual ~HeapAllocator();

			virtual boolean init( Size capacity, Allocator* parentAllocator );
			virtual void release();
			virtual void* allocate( Size size, Size align = 4 ) = 0;
			virtual void* reallocate( void* p, Size size, Size align = 4 );
			virtual void deallocate( void* p );

			virtual boolean allocated( void* p );
			inline virtual Size getDataSize( void* p );
			inline virtual Size getCapacity() const { return capacity; }
			inline virtual Size getTotalAllocatedSize() const { return allocatedSize; }
			inline virtual int getTotalAllocationCount() const { return allocationCount; }
			inline virtual Size getFragmentSize() const { return fragmentSize; }

			void printStats();
		};
	}
}