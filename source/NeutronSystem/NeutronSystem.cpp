#include "NeutronSystem.h"
#include "NeutronFoundation/Memory.h"

namespace Neutron
{
	namespace System
	{
		NeutronSystem::NeutronSystem()
			:exitFlag( false )
		{
		}

		NeutronSystem::~NeutronSystem()
		{
		}

		boolean NeutronSystem::init( const char* path )
		{
			boolean ret = true;
			ret = ret && Memory::init();
			ret = ret && taskManager.init( 4, 128 );
			return true;
		}

		void NeutronSystem::release()
		{
			taskManager.release();
			Memory::release();
		}

		void NeutronSystem::update()
		{
			taskManager.update();

			if( taskManager.isIdle() )
			{
				shutdown();
			}
		}

		void NeutronSystem::run()
		{
			while( !exitFlag )
			{
				update();
			}
		}

		NeutronSystem& getSystem()
		{
			static NeutronSystem systemStub;
			return systemStub;
		}
	};
}