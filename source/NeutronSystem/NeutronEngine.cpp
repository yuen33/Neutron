#include "NeutronEngine.h"
#include "ProcessingModule.h"

namespace Neutron
{
	namespace Engine
	{
		NeutronEngine::NeutronEngine()
		{
		}

		NeutronEngine::~NeutronEngine()
		{
		}

		boolean NeutronEngine::init()
		{
			return true;
		}

		void NeutronEngine::release()
		{
		}

		void NeutronEngine::runModule( ProcessingModulePtr module )
		{
			module->assembleUnit();

			bool ret = true;
			while( ret )
			{
				ret = module->updateUnit();
			}
		}

		NeutronEngine& getEngine()
		{
			static NeutronEngine engineStub;
			return engineStub;
		}
	}
}