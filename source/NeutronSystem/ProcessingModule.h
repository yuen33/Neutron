#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/HashMap.h"
#include "Device.h"
#include "Variable.h"
#include "Pin.h"
#include "ProcessingUnit.h"

using Neutron::Container::HashMap;
using Neutron::System::Device;

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE ProcessingModule
		{
			HashMap<uint32, VariablePtr>						variables;
			HashMap<uint32, PinPtr>								pins;
			HashMap<uint32, Array<ProcessingUnitPtr> >			processingUnits;

			// control
			boolean												enabled;

		public:
			ProcessingModule();
			virtual ~ProcessingModule();
		};
	}
}