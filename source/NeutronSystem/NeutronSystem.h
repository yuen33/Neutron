#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/TaskManager.h"
#include "NeutronFoundation/MessageBus.h"
#include "NeutronPluginManager.h"
#include "DeviceManager.h"
#include "ResourceManager.h"

using Neutron::Concurrent::TaskManager;
using Neutron::Utility::MessageBus;
using Neutron::Utility::PluginManager;

namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE NeutronSystem
		{
			TaskManager						taskManager;
			MessageBus<Message::MC_System>	messageBus;
			NeutronPluginManager			pluginManager;
			DeviceManager					deviceManager;

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
			inline DeviceManager& getDeviceManager() { return deviceManager; }
			inline MessageBus<Message::MC_System>& getMessageBus() { return messageBus; }
			inline void shutdown() { exitFlag = true; }
		};

		inline NEUTRON_CORE NeutronSystem& getSystem();
	};
}