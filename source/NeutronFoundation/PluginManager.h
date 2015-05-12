#pragma once

#include "NeutronFoundationCommon.h"
#include "HashMap.h"
#include "String.h"

using Neutron::Container::HashMap;
using Neutron::Container::String;

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE Plugin
		{
		public:
			Plugin();
			virtual ~Plugin();
		};

		typedef Plugin* (*PluginCreateFunc)();
		typedef void (*PluginDestroyFunc)( Plugin* );

		class NEUTRON_FOUNDATION_CORE PluginManager
		{
			struct PluginInfo
			{
				String					path;
				NEUTRON_PLUGIN_HANDLE	handle;
				PluginCreateFunc		createFunc;
				PluginDestroyFunc		destroyFunc;
				Plugin*					plugin;
			};

			HashMap<uint32, PluginInfo*> plugins;

		public:
			boolean loadPlugin( const char* path );
			void unloadPlugin( const char* path );
			virtual void onPluginLoaded( const char* path, Plugin* plugin );

			boolean loadedPlugin( const char* path );
			Plugin* findPlugin( const char* path );
		};
	}
}