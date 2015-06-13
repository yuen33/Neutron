#pragma once

#include "EngineDefine.h"
#include "NeutronFoundation/HashMap.h"
#include "NeutronFoundation/String.h"

using Neutron::Container::HashMap;
using Neutron::Container::String;

namespace Neutron
{
	namespace Engine
	{
		class Module
		{
			HashMap<uint32, VariablePtr>			variables;
			HashMap<uint32, VPUPtr>					vpus;

		public:
			Module();
			virtual ~Module();

			
		};
	}
}