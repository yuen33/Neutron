#pragma once

#include "PluginManager.h"
#include "Hash.h"

namespace Neutron
{
	namespace Utility
	{
		// Plugin
		Plugin::Plugin()
		{
		}

		Plugin::~Plugin()
		{
		}

		// PluginManager
		boolean PluginManager::loadPlugin( const char* path )
		{
			// load 
			NEUTRON_PLUGIN_HANDLE handle = Neutron::loadPlugin( path );
			if( !handle )
			{
				return false;
			}

			// get entry & exit functions
			PluginCreateFunc createFunc = (PluginCreateFunc)Neutron::getPluginSymbol( handle, "createPlugin" );
			PluginDestroyFunc destroyFunc = (PluginDestroyFunc)Neutron::getPluginSymbol( handle, "DestroyPlugin" );
			if( !createFunc || !destroyFunc )
			{
				return false;
			}

			// create plugin
			Plugin* plugin = createFunc();
			if( !plugin )
			{
				return false;
			}

			PluginInfo* newInfo = new PluginInfo;
			assert( newInfo );
			newInfo->path = path;
			newInfo->handle = handle;
			newInfo->createFunc = createFunc;
			newInfo->destroyFunc = destroyFunc;
			newInfo->plugin = plugin;
			
			plugins.add( Math::Hash::DJB32( path ), newInfo );

			onPluginLoaded( path, plugin );

			return true;
		}

		void PluginManager::unloadPlugin( const char* path )
		{
			HashMap<uint32, PluginInfo*>::Iterator it = plugins.find( Math::Hash::DJB32( path ) );
			if( it != plugins.end() )
			{
				PluginInfo* info = it.value();
				assert( info );
				assert( info->destroyFunc );
				info->destroyFunc( info->plugin );
				Neutron::unloadPlugin( info->handle );
				delete info;
			}

			plugins.remove( it );
		}

		Plugin* PluginManager::findPlugin( const char* path )
		{
			HashMap<uint32, PluginInfo*>::Iterator it = plugins.find( Math::Hash::DJB32( path ) );
			return it != plugins.end() ? it.value()->plugin : 0;
		}

		boolean PluginManager::loadedPlugin( const char* path )
		{
			HashMap<uint32, PluginInfo*>::Iterator it = plugins.find( Math::Hash::DJB32( path ) );
			return it != plugins.end();
		}

		void PluginManager::onPluginLoaded( const char* path, Plugin* plugin )
		{
		}
	}
}