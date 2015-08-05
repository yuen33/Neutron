#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/String.h"

using Neutron::Engine::ResourcePtr;
using Neutron::Container::String;

namespace Neutron
{
	namespace System
	{
		// device type
		enum : int
		{
			DT_Unknown,
			DT_SystemDevice,
			DT_RenderDevice
		};

		class NEUTRON_CORE Device : public RCObject
		{
		protected:
			int deviceType;
			String name;
			NeutronPlugin* owner;

			virtual void deleteMethod( RCObject* object );

		public:
			Device( NeutronPlugin* owner );
			virtual ~Device();

			virtual boolean init();
			virtual void release() = 0;

			void onPluginRelease();

			inline int getType() const { return deviceType; }
			inline const char* getName() const { return name.getCStr(); }
			inline NeutronPlugin* getOwner() const { return owner; }
		};
	}
}