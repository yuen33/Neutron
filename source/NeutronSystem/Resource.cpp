#include "Resource.h"
#include "Device.h"

namespace Neutron
{
	namespace Engine
	{
		Resource::Resource( Device* owner )
			: resourceType( RT_Unknown )
			, owner( owner )
		{
		}

		Resource::~Resource()
		{
		}
	}
}