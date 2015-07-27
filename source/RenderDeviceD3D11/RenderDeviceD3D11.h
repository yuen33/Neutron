#pragma once

#include "NeutronSystem/RenderDevice.h"
#include "RenderDeviceEnumerator.h"

namespace Neutron
{
	namespace System
	{
		class RenderDeviceD3D11 : public RenderDevice
		{
			RenderDeviceEnumerator enumerator;

		public:
			RenderDeviceD3D11( NeutronPlugin* owner );
			virtual ~RenderDeviceD3D11();

			virtual boolean init();
			void release();

			virtual InputStreamPtr	createInputStream();
			virtual BufferPtr		createBuffer();
			virtual TexturePtr		createTexture();
			virtual SamplerPtr		createSampler();
			virtual ShaderPtr		createShader();

			inline virtual const wchar* getDesktopName() const { return enumerator.getDesktopOutpuName(); }
			inline virtual int getDesktopWidth() const { return enumerator.getDesktopWidth(); }
			inline virtual int getDesktopHeight() const { return enumerator.getDesktopHeight(); }
			inline virtual int getDesktopAdapterIndex() const { return enumerator.getDesktopAdapterIndex(); }
		};
	}
}