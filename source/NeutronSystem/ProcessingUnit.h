#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/HashMap.h"
#include "Device.h"
#include "Variable.h"
#include "Pin.h"

using Neutron::System::Device;
using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Engine
	{
		enum : int
		{
			PUT_Known,
			PUT_Window
		};

		class NEUTRON_CORE ProcessingUnit : public RCObject
		{
		protected:
			int										processingUnitType;
			Device*									owner;

			HashMap<uint32, VariablePtr>			variables;
			HashMap<uint32, PinPtr>					pins;

			// control
			boolean									enabled;

		public:
			ProcessingUnit( Device* owner );
			virtual ~ProcessingUnit();

			inline int getProcessingUnitType() const { return processingUnitType; }
		};
	}
}