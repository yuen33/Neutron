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
			RenderDevice( NeutronPlugin* owner );
			virtual ~RenderDevice();

			virtual InputStreamPtr	createInputStream() = 0;
			virtual BufferPtr		createBuffer() = 0;
			virtual TexturePtr		createTexture() = 0;
			virtual SamplerPtr		createSampler() = 0;
			virtual ShaderPtr		createShader() = 0;

			virtual const wchar* getDesktopName() const = 0;
			virtual int getDesktopWidth() const = 0;
			virtual int getDesktopHeight() const = 0;
			virtual int getDesktopAdapterIndex() const = 0;
		};
	}
}