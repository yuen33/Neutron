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
			
			virtual boolean init();
			virtual void release();

			virtual Device* createDevice( const char* name );
			virtual void destroyDevice( Device* device );

			virtual const char* getVendorName();
			virtual Version getVersion();
		};
	}
}

extern "C"
{
	NEUTRON_RENDERDEVICE_D3D11_CORE Plugin* createPlugin();
	NEUTRON_RENDERDEVICE_D3D11_CORE void destroyPlugin( Plugin* plugin );
}