#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		class InputStream : public Resource
		{
		public:
			InputStream( Device* owner );
			virtual ~InputStream();
		};
	}
}