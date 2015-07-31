#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Shader : public Resource
			{
			public:
				Shader( Device* owner );
				virtual ~Shader();
			};
		}
	}
}