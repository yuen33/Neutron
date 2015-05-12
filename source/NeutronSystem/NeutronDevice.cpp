#include "NeutronDevice.h"
#include "NeutronResource.h"

namespace Neutron
{
	namespace System
	{
		NeutronDevice::NeutronDevice()
		{
		}

		NeutronDevice::~NeutronDevice()
		{
		}

		void NeutronDevice::destroyResource( NeutronResource* resource )
		{
			if( resource )
			{
				delete resource;
			}
		}
	}
}