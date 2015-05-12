#include "NeutronResource.h"

namespace Neutron
{
	namespace System
	{
		NeutronResource::NeutronResource( NeutronDevice* owner )
			:owner( owner )
		{
		}

		NeutronResource::~NeutronResource()
		{
		}


	}
}