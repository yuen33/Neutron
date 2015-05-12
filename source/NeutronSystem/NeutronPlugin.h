#include "NeutronSystemCommon.h"
#include "NeutronFoundation/PluginManager.h"

using Neutron::Utility::Plugin;

namespace Neutron
{
	namespace System
	{
		class NeutronDevice;
		class NEUTRON_CORE NeutronPlugin : Plugin
		{
		public:
			NeutronPlugin();
			virtual ~NeutronPlugin();

			virtual int getDeviceCount();
			virtual NeutronDevice* getDevice( int index );
		};
	}
}