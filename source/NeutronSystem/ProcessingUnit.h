#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/HashMap.h"
#include "Device.h"
#include "Parameter.h"
#include "Pin.h"

using Neutron::System::Device;
using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Engine
	{
		enum : int
		{
			PUT_Unknown,
			PUT_Module,
			PUT_Renderer,
			PUT_Window
		};

		class NEUTRON_CORE ProcessingUnit : public RCObject
		{
		protected:
			int												processingUnitType;
			Device*											owner;
			HashMap<uint32, PinPtr>							pins;

			boolean											enabled;

			void deleteMethod( RCObject* object );
			void getIdlePins( Array<PinPtr>& idlePins );

		public:
			ProcessingUnit( Device* owner );
			virtual ~ProcessingUnit();

			virtual void release() = 0;

			void registerPin( const char* name, PinPtr pin );
			void unregisterPin( const char* name );

			virtual boolean assembleUnit();
			virtual boolean updateUnit();

			void printIdlePins();

			HashMap<uint32, PinPtr>& getPins() { return pins; }
			PinPtr getPin( const char* name );
			inline int getProcessingUnitType() const { return processingUnitType; }
			inline boolean isEnabled() const { return enabled; }
		};
	}
}