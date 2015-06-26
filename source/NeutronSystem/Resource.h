#pragma once

#include "NeutronSystemCommon.h"

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE Resource : public RCObject
		{
		public:
			Resource() {};
			virtual ~Resource() {};
		};
	}
}