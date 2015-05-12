#include "NeutronD3D11Plugin.h"

namespace Neutron
{
	NeutronD3D11Plugin::NeutronD3D11Plugin()
	{
	}

	NeutronD3D11Plugin::~NeutronD3D11Plugin()
	{
	}

	int NeutronD3D11Plugin::getDeviceCount()
	{
		return 1;
	}

	NeutronDevice* NeutronD3D11Plugin::getDevice( int index )
	{
		return 0;
	}

	NeutronD3D11Plugin* createPlugin()
	{
		NeutronD3D11Plugin* newPlugin = new NeutronD3D11Plugin();
		assert( newPlugin );
		return newPlugin;
	}

	void destroyPlugin( NeutronPlugin* plugin )
	{
		if( plugin )
		{
			delete static_cast<NeutronD3D11Plugin*>( plugin );
		}
	}
}