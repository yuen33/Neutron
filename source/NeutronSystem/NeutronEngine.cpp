#include "NeutronEngine.h"

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

		NeutronEngine& getEngine()
		{
			static NeutronEngine engineStub;
			return engineStub;
		}
	}
}