#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/PluginManager.h"
#include "NeutronFoundation/TaskManager.h"

using Neutron::Utility::TaskManager;
using Neutron::Utility::PluginManager;

namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE NeutronSystem
		{
			TaskManager		taskManager;
			PluginManager	pluginManager;

			boolean exitFlag;

		public:
			NeutronSystem();
			virtual ~NeutronSystem();

			boolean init( const char* path = 0 );
			void release();

			void update();
			void run();

			inline TaskManager& getTaskManager() { return taskManager; }
			inline PluginManager& getPluginManager() { return pluginManager; }
			inline void shutdown() { exitFlag = true; }
		};

		inline NEUTRON_CORE NeutronSystem& getSystem();
	};
}