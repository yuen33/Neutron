#include "DeviceManager.h"
#include "NeutronFoundation/Hash.h"
#include "NeutronSystem.h"
#include "NeutronPlugin.h"
#include "Log.h"
#include "SystemDevice.h"

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
			// create system device
			systemDevice = SystemDevicePtr( new SystemDevice( 0 ) );
			if( !systemDevice->init() )
			{
				return false;
			}

			return true;
		}

		void DeviceManager::release()
		{
			// release system device
			systemDevice->release();
			systemDevice = 0;
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
			HashMap<uint32, DeviceInfo>::Iterator itDeviceInfo = deviceInfo.find( Math::Hash::DJB32( name ) );
			if( itDeviceInfo != deviceInfo.end() )
			{
				Device* device = 0;
				if( itDeviceInfo.value().plugin != 0 )
				{
					device = itDeviceInfo.value().plugin->createDevice( name );
				}
				
				assert( device );
				if( device )
				{
					HashMap<int, Array<Device*> >::Iterator itDevice = devices.find( itDeviceInfo.value().deviceType );
					if( itDevice != devices.end() )
					{
						itDevice.value().add( device );
					}
					else
					{
						Array<Device*> newDeviceArray;
						newDeviceArray.add( device );
						devices.add( itDeviceInfo.value().deviceType, newDeviceArray );
					}
				}

				return DevicePtr( device );
			}

			return DevicePtr::null;
		}
	}
}