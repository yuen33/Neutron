#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		class Shader : public Resource
		{
		public:
			Shader( Device* owner );
			virtual ~Shader();
		};
	}
}