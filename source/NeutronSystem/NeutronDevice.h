#pragma once

#include "NeutronSystemCommon.h"

namespace Neutron
{
	namespace System
	{
		class NeutronResource;
		class NEUTRON_CORE NeutronDevice
		{
		public:
			NeutronDevice();
			virtual ~NeutronDevice();

			virtual void destroyResource( NeutronResource* reource );
		};
	}
}