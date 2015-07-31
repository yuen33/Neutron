#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Sampler : public Resource
			{
			public:
				Sampler( Device* owner );
				virtual ~Sampler();
			};
		}
	}
}