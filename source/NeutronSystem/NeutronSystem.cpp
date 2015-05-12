#include "NeutronSystem.h"
#include "NeutronFoundation/Memory.h"

namespace Neutron
{
	namespace System
	{
		NeutronSystem::NeutronSystem()
		{
		}

		NeutronSystem::~NeutronSystem()
		{
		}

		boolean NeutronSystem::init( const char* path )
		{
			Memory::init();
			return true;
		}

		void NeutronSystem::release()
		{
			Memory::release();
		}

		NeutronSystem getSystem()
		{
			static NeutronSystem systemStub;
			return systemStub;
		}
	}
}