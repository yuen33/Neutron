#include "NeutronPluginManager.h"
#include "NeutronPlugin.h"
#include "NeutronFoundation/String.h"
#include "Log.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace System
	{
		NeutronPluginManager::NeutronPluginManager()
		{
		}

		NeutronPluginManager::~NeutronPluginManager()
		{
		}

		void NeutronPluginManager::onPluginLoaded( const char* path, Plugin* plugin )
		{
			Log::message( "NeutronPluginManager", String::format( "Load plugin %s\n", path ).getCStr() );
			NeutronPlugin* p = static_cast<NeutronPlugin*>( plugin );
			if( !p->init() )
			{
				unloadPlugin( path );
			}
		}

		void NeutronPluginManager::onPluginUnload( const char* path, Plugin* plugin )
		{
			NeutronPlugin* p = static_cast<NeutronPlugin*>( plugin );
			p->release();
			Log::message( "NeutronPluginManager", String::format( "Unload plugin %s\n", path ).getCStr() );
		}
	}
}