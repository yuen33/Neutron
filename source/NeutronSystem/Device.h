#pragma once

#include "NeutronSystemCommon.h"

using Neutron::Engine::Resource;

namespace Neutron
{
	namespace System
	{
		enum : int
		{
			SystemDevice,
			RenderDevice
		};

		class NEUTRON_CORE Device : public RCObject
		{
		public:
			Device();
			virtual ~Device();

			virtual Resource* makeResource( int resourceType );
			virtual void destroyResource( Resource* resource );
		};
	}
}