#pragma once

#include "NeutronSystemCommon.h"

namespace Neutron
{
	namespace Engine
	{
		enum : int
		{
			Image,
			InputStream,
			Buffer,
			Texture,
			Sampler,
			Shader,
			Viewport,
			Window
		};

		class NEUTRON_CORE Resource : public RCObject
		{
		public:
			Resource() {};
			virtual ~Resource() {};
		};
	}
}