#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		class Sampler : public Resource
		{
		public:
			Sampler( Device* owner );
			virtual ~Sampler();
		};
	}
}