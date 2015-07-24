#include "RenderDeviceD3D11Plugin.h"

namespace Neutron
{
	namespace System
	{
		RenderDeviceD3D11Plugin::RenderDeviceD3D11Plugin()
		{
		}

		RenderDeviceD3D11Plugin::~RenderDeviceD3D11Plugin()
		{
		}

		Device* RenderDeviceD3D11Plugin::makeDevice( int deviceType )
		{
			return 0;
		}

		void RenderDeviceD3D11Plugin::destroyDevice( Device* device )
		{
		}
	}
}