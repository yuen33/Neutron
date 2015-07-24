#pragma once

#include "RenderDeviceD3D11Common.h"
#include "NeutronSystem/NeutronPlugin.h"

namespace Neutron
{
	namespace System
	{
		class NEUTRON_RENDERDEVICE_D3D11_CORE RenderDeviceD3D11Plugin : public NeutronPlugin
		{
		public:
			RenderDeviceD3D11Plugin();
			virtual ~RenderDeviceD3D11Plugin();

			virtual Device* makeDevice( int deviceType );
			virtual void destroyDevice( Device* device );
		};
	}
}