#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/HashMap.h"
#include "Pin.h"
#include "Variable.h"

using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE VPU
		{
			HashMap<uint32, VariablePtr>			variables;
			HashMap<uint32, PinPtr>					pins;

			// control
			boolean									enabled;

		public:
			VPU();
			virtual ~VPU();

			inline void setEnabled( boolean value ) { enabled = value; }
			inline boolean getEnabled() const { return enabled; }
		};
	}
}