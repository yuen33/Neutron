#include "InputStream.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
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
}