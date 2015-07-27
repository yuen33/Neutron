#include "Buffer.h"

namespace Neutron
{
	namespace Engine
	{
		Buffer::Buffer( Device* owner )
			: Resource( owner )
		{
			resourceType = RT_Buffer;
		}

		Buffer::~Buffer()
		{
		}
	}
}