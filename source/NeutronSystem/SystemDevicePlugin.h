#pragma once

#include "NeutronPlugin.h"

namespace Neutron
{
	namespace System
	{
		class SystemDevicePlugin : public NeutronPlugin
		{
			SystemDevicePlugin();
			virtual ~SystemDevicePlugin();

			virtual boolean init();
			virtual void release();

			virtual Device* createDevice( const char* name );
			virtual void destroyDevice( Device* device );

			virtual const char* getVendorName();
			virtual Version getVersion();
		};
	}
}