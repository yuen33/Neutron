#include "RenderDeviceD3D11Plugin.h"
#include "RenderDeviceD3D11.h"
#include "NeutronFoundation/Hash.h"
#include "NeutronSystem/NeutronSystem.h"
#include "NeutronSystem/DeviceManager.h"
#include "NeutronSystem/Log.h"

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

		boolean RenderDeviceD3D11Plugin::init()
		{
			getSystem().getDeviceManager().registerDevice( "RenderDevice.D3D11", DT_RenderDevice, this );

			return true;
		}

		void RenderDeviceD3D11Plugin::release()
		{
			getSystem().getDeviceManager().unregisterDevice( "RenderDevice.D3D11" );
		}

		Device* RenderDeviceD3D11Plugin::createDevice( const char* name )
		{
			uint32 hashValue = Math::Hash::DJB32( name );

			if( hashValue == Math::Hash::DJB32( "RenderDevice.D3D11" ) )
			{
				return new RenderDeviceD3D11( this );
			}

			return 0;
		}

		void RenderDeviceD3D11Plugin::destroyDevice( Device* device )
		{
			if( device )
			{
				uint32 hashValue = Math::Hash::DJB32( device->getName() );
				if( hashValue == Math::Hash::DJB32( "RenderDevice.D3D11" ) )
				{
					delete static_cast<RenderDeviceD3D11*>( device );
				}
			}
		}

		const char* RenderDeviceD3D11Plugin::getVendorName()
		{
			return "Neutron";
		}

		RenderDeviceD3D11Plugin::Version RenderDeviceD3D11Plugin::getVersion()
		{
			return Version( 0, 1, 0, 0 );
		}
	}
}

Plugin* createPlugin()
{
	return new Neutron::System::RenderDeviceD3D11Plugin();
}

void destroyPlugin( Plugin* plugin )
{
	if( plugin )
	{
		delete static_cast<Neutron::System::RenderDeviceD3D11Plugin*>( plugin );
	}
}