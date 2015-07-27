#include "DeviceManager.h"
#include "NeutronFoundation/Hash.h"
#include "NeutronSystem.h"
#include "NeutronPlugin.h"
#include "Log.h"

namespace Neutron
{
	namespace System
	{
		DeviceManager::DeviceManager()
		{
		}

		DeviceManager::~DeviceManager()
		{
		}

		boolean DeviceManager::init()
		{			
			subscriberPluginRelease = getSystem().getMessageBus().subscribe<Message::MessagePluginRelease>( &DeviceManager::handlePluginRelease );

			return true;
		}

		void DeviceManager::release()
		{
			getSystem().getMessageBus().unsubscribe( subscriberPluginRelease );
		}

		void DeviceManager::registerDevice( const char* name, int deviceType, NeutronPlugin* plugin )
		{
			if( name != 0 && name[0] != '\0' && deviceType != DT_Unknown && plugin != 0 )
			{
				Log::message( "DeviceManager", String::format( "Register device %s type = %d\n", name, deviceType ).getCStr() );
				deviceInfo.add( Math::Hash::DJB32( name ), DeviceInfo( deviceType, name, plugin ) );
			}
		}

		void DeviceManager::unregisterDevice( const char* name )
		{
			deviceInfo.remove( Math::Hash::DJB32( name ) );
			Log::message( "DeviceManager", String::format( "Unregister device %s\n", name ).getCStr() );
		}

		DevicePtr DeviceManager::createDevice( const char* name )
		{
			HashMap<uint32, DeviceInfo>::Iterator it = deviceInfo.find( Math::Hash::DJB32( name ) );
			if( it != deviceInfo.end() )
			{
				Device* device = 0;
				if( it.value().plugin != 0 )
				{
					device = it.value().plugin->createDevice( name );
				}
				
				assert( device );
				if( device )
				{
					devices.add( device );
				}

				return DevicePtr( device );
			}

			return DevicePtr::null;
		}

		void DeviceManager::onPluginRelease( NeutronPlugin* plugin ) 
		{
			if( plugin )
			{
				for( int i = 0; i < devices.getCount(); ++i )
				{
					if( devices[i]->getOwner() == plugin )
					{
						devices[i]->onPluginRelease();
					}
				}
			}
		}

		void DeviceManager::handlePluginRelease( Message::MessagePluginRelease message )
		{
			getSystem().getDeviceManager().onPluginRelease( message.plugin );
		}
	}
}