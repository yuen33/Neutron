#pragma once

#include "Platform.h"
#include "Allocator.h"

namespace Neutron
{
	namespace Memory
	{
		class NEUTRON_FOUNDATION_CORE HostAllocator : public Allocator
		{
			int allocationCount;

		public:
			HostAllocator() : allocationCount( 0 ) {}
			virtual ~HostAllocator() {};

			inline virtual bool init( Size capacity, Allocator* parentAllocator ) { return true; }
			inline virtual void release() {}
			inline virtual void* allocate( Size size, Size align = 4 ) { ++allocationCount; return alloc( size ); }
			inline virtual void* reallocate( void* p, Size size, Size align = 4 ) { return realloc( p, size ); }
			inline virtual void deallocate( void* p ) { if( p ) free( p ); }
			
			inline virtual boolean allocated( void* p ) { return false; }
			inline virtual Size getDataSize( void* p ) { return SIZE_NOT_TRACKED; }
			inline virtual Size getCapacity() const { return CAPACITY_UNKNOWN; }
			inline virtual Size getTotalAllocatedSize() const { return SIZE_NOT_TRACKED; }
			inline virtual int getTotalAllocationCount() const { return allocationCount; }
		};
	}
}