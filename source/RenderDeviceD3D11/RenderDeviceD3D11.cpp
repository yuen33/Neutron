#include "RenderDeviceD3D11.h"
#include "NeutronSystem/Resource.h"
#include "NeutronSystem/Log.h"

#include "InputStreamD3D11.h"
#include "BufferD3D11.h"
#include "TextureD3D11.h"
#include "SamplerD3D11.h"
#include "ShaderD3D11.h"

namespace Neutron
{
	namespace System
	{
		RenderDeviceD3D11::RenderDeviceD3D11( NeutronPlugin* owner )
			: RenderDevice( owner )
		{
			enumerator.enumerate();
			enumerator.printDeviceInfo();
		}

		RenderDeviceD3D11::~RenderDeviceD3D11()
		{

		}

		boolean RenderDeviceD3D11::init()
		{
			return true;
		}

		void RenderDeviceD3D11::release()
		{
		}

		InputStreamPtr RenderDeviceD3D11::createInputStream()
		{
			return InputStreamPtr::null;
		}

		BufferPtr RenderDeviceD3D11::createBuffer()
		{
			return BufferPtr::null;
		}

		TexturePtr RenderDeviceD3D11::createTexture()
		{
			return TexturePtr::null;
		}

		SamplerPtr RenderDeviceD3D11::createSampler()
		{
			return SamplerPtr::null;
		}

		ShaderPtr RenderDeviceD3D11::createShader()
		{
			return ShaderPtr::null;
		}
	}
}