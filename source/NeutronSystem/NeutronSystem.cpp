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
			ret = ret && taskManager.init( 8, 1024 );
			ret = ret && pluginManager.init( "plugins/" );
			ret = ret && deviceManager.init();
			return true;
		}

		void NeutronSystem::release()
		{
			deviceManager.release();
			pluginManager.release();
			taskManager.release();
			Memory::release();
		}

		void NeutronSystem::update()
		{
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