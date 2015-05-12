#pragma once

#include "NeutronFoundationCommon.h"

namespace Neutron
{
	namespace Memory
	{
		static inline void* alignForward( void* p, Size align )
		{
			if( align )
			{
				uintptr pi = uintptr( p );
				pi += pi & ( align - 1 );
				return (void*)pi;
			}

			return p;
		}

		class NEUTRON_FOUNDATION_CORE Allocator
		{
		public:
			enum
			{
				CAPACITY_UNKNOWN = 0XFFFFFFFF,
				SIZE_NOT_TRACKED = 0XFFFFFFFF,
				ALLOCATION_NOT_TRACKED = 0XFFFFFFFF
			};

		public:
			Allocator() {};
			virtual ~Allocator() {};

			virtual boolean init( Size capacity, Allocator* parentAllocator ) = 0;
			virtual void release() = 0;
			virtual void* allocate( Size size, Size align = 4 ) = 0;
			virtual void* reallocate( void* p, Size size, Size align ) = 0;
			virtual void deallocate( void* p ) = 0;

			virtual bool allocated( void* p ) = 0;
			virtual Size getDataSize( void* p ) = 0;
			virtual Size getCapacity() const = 0;
			virtual Size getTotalAllocatedSize() const = 0;
			virtual int getTotalAllocationCount() const = 0;
		};
	}
}