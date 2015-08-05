#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/String.h"
#include "NeutronFoundation/HashMap.h"
#include "Device.h"

using Neutron::Container::String;
using Neutron::Container::HashMap;

namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE DeviceManager
		{
		public:
			struct DeviceInfo
			{
				int deviceType;
				String name;
				NeutronPlugin* plugin;

				DeviceInfo()
				{
				}

				DeviceInfo( int deviceType, const char* name, NeutronPlugin* plugin )
					: deviceType( deviceType )
					, name( name )
					, plugin( plugin )
				{
				}
			};

		private:
			HashMap<uint32, DeviceInfo>			deviceInfo;
			HashMap<int, Array<DevicePtr> >		devices;
			DevicePtr							systemDevice;

		public:
			DeviceManager();
			virtual ~DeviceManager();

			boolean init();
			void release();

			void registerDevice( const char* name, int deviceType, NeutronPlugin* plugin );
			void unregisterDevice( const char* name );

			DevicePtr createDevice( const char* deviceTypeName );
			inline DevicePtr getSystemDevice() const { return systemDevice; }
		};
	}
}