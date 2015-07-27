#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		class Window : public Resource
		{
		public:
			Window( Device* owner );
			virtual ~Window();
		};
	}
}