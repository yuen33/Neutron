#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/PluginManager.h"
#include "Device.h"

using Neutron::Utility::Plugin;

namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE NeutronPlugin : public Plugin
		{
		public:
			NeutronPlugin();
			virtual ~NeutronPlugin();

			virtual Device* makeDevice( int deviceType );
			virtual void destroyDevice( Device* device );
		};
	}
}