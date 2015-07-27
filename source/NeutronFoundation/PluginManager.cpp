#pragma once

#include "PluginManager.h"
#include "Array.h"
#include "Hash.h"

using Neutron::Container::Array;

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
		PluginManager::PluginManager()
		{
		}

		PluginManager::~PluginManager()
		{
		}

		boolean PluginManager::init( const char* pluginFolder )
		{
			Array<String> pluginPaths;
			String folderPath = pluginFolder;
			
#if defined NEUTRON_WINDOWS_DESKTOP
			WIN32_FIND_DATAA context;
			memset( &context, 0, sizeof( context ) );
			HANDLE fileHandle = FindFirstFileA( ( folderPath + "*.dll" ).getCStr(), &context );

			if( fileHandle != INVALID_HANDLE_VALUE )
			{
				pluginPaths.add( folderPath + context.cFileName );
			}

			while( FindNextFileA( fileHandle, &context ) )
			{
				pluginPaths.add( folderPath + context.cFileName );
			}

			FindClose( fileHandle );
#endif

			for( int i = 0; i < pluginPaths.getCount(); ++i )
			{
				loadPlugin( pluginPaths[i].getCStr() );
			}

			return true;
		}

		void PluginManager::release()
		{
			for( HashMap<uint32, PluginInfo*>::Iterator it = plugins.begin(); it != plugins.end(); ++it )
			{
				PluginInfo* info = it.value();
				assert( info );
				assert( info->destroyFunc );

				onPluginUnload( info->path.getCStr(), info->plugin );

				info->destroyFunc( info->plugin );
				Neutron::unloadPlugin( info->handle );
				delete info;
			}

			plugins.clear();
		}

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
			PluginDestroyFunc destroyFunc = (PluginDestroyFunc)Neutron::getPluginSymbol( handle, "destroyPlugin" );
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

				onPluginUnload( path, info->plugin );

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

		void PluginManager::onPluginUnload( const char* path, Plugin* plugin )
		{
		}
	}
}