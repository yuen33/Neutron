#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE InputStream : public Resource
			{
			public:
				InputStream( Device* owner );
				virtual ~InputStream();
			};
		}
	}
}