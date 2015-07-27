#include "InputStream.h"

namespace Neutron
{
	namespace Engine
	{
		InputStream::InputStream( Device* owner )
			: Resource( owner )
		{
			resourceType = RT_InputStream;
		}

		InputStream::~InputStream()
		{
		}
	}
}