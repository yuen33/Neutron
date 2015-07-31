#include "Buffer.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			Buffer::Buffer( Device* owner )
				: Resource( owner )
				, bufferType( BT_Unknown )
			{
				resourceType = RT_Buffer;
			}

			Buffer::~Buffer()
			{
			}
		}
	}
}