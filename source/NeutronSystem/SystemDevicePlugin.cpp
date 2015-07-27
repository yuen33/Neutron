#include "SystemDevicePlugin.h"
#include "NeutronFoundation/Hash.h"
#include "SystemDevice.h"
#include "NeutronSystem.h"

namespace Neutron
{
	namespace System
	{
		SystemDevicePlugin::SystemDevicePlugin()
		{
		}

		SystemDevicePlugin::~SystemDevicePlugin()
		{
		}

		boolean SystemDevicePlugin::init()
		{
			getSystem().getDeviceManager().registerDevice( "SystemDevice", DT_SystemDevice, this );

			return true;
		}

		void SystemDevicePlugin::release()
		{
			getSystem().getDeviceManager().unregisterDevice( "SystemDevice" );
		}

		Device* SystemDevicePlugin::createDevice( const char* name )
		{
			uint32 hashValue = Math::Hash::DJB32( name );
			if( hashValue == Math::Hash::DJB32( "SystemDevice" ) )
			{
				return new SystemDevice( this );
			}

			return 0;
		}

		void SystemDevicePlugin::destroyDevice( Device* device )
		{
			if( device )
			{
				uint32 hashValue = Math::Hash::DJB32( device->getName() );
				if( hashValue == Math::Hash::DJB32( "SystemDevice" ) )
				{
					delete static_cast<SystemDevice*>( device );
				}
			}
		}

		const char* SystemDevicePlugin::getVendorName()
		{
			return "Neutron";
		}

		NeutronPlugin::Version SystemDevicePlugin::getVersion()
		{
			return NeutronPlugin::Version( 0, 1, 0, 0 );
		}
	}
}