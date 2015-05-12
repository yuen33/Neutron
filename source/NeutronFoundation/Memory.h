#pragma once

#include "HostAllocator.h"
#include "SystemAllocator.h"

namespace Neutron
{
	namespace Memory
	{
		static inline Allocator* getHostAllocator()
		{
			static HostAllocator stubGlobalHostAllocator;
			return &stubGlobalHostAllocator;
		}

		static inline Allocator* getSystemAllocator()
		{
			static SystemAllocator stubGlobalSystemAllocator;
			return &stubGlobalSystemAllocator;
		}

		static inline bool init()
		{
			bool ret = true;
			ret = ret && getHostAllocator()->init( 0, 0 );
			ret = ret && getSystemAllocator()->init( 0, getHostAllocator() );
			return ret;
		}

		static inline void release()
		{
			getSystemAllocator()->release();
			getHostAllocator()->release();
		}

		static inline void printStats()
		{
			static_cast<SystemAllocator*>( getSystemAllocator() )->printStats();
		}
	}
}

static inline void* operator new( Neutron::Size size ) { return Neutron::Memory::getSystemAllocator()->allocate( size ); }
static inline void* operator new[]( Neutron::Size size ) { return Neutron::Memory::getSystemAllocator()->allocate( size ); }
static inline void operator delete( void* p ) { Neutron::Memory::getSystemAllocator()->deallocate( p ); }
static inline void operator delete[]( void* p ) { Neutron::Memory::getSystemAllocator()->deallocate( p ); }
static inline void operator delete( void* p, Neutron::Size size ) { Neutron::Memory::getSystemAllocator()->deallocate( p ); }
static inline void operator delete[]( void* p, Neutron::Size size ) { Neutron::Memory::getSystemAllocator()->deallocate( p ); }	