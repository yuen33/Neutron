#pragma once

#include "Device.h"

using namespace Neutron::Engine;

namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE RenderDevice : public Device
		{
		public:
			RenderDevice();
			virtual ~RenderDevice();

			InputStreamPtr createInputStream();
			BufferPtr createBuffer();
			TexturePtr createTexture();
			SamplerPtr createSampler();
			ShaderPtr createShader();


		};
	}
}