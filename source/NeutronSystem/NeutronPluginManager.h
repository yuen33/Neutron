#include "NeutronSystemCommon.h"
#include "NeutronFoundation/PluginManager.h"

using Neutron::Utility::Plugin;
using Neutron::Utility::PluginManager;

namespace Neutron
{
	namespace System
	{
		class NeutronPluginManager : public PluginManager
		{
		public:
			NeutronPluginManager();
			virtual ~NeutronPluginManager();

			virtual void onPluginLoaded( const char* path, Plugin* plugin );
			virtual void onPluginUnload( const char* path, Plugin* plugin );
		};
	}
}