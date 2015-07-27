#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		class Buffer : public Resource
		{
		public:
			Buffer( Device* owner );
			virtual ~Buffer();
		};
	}
}