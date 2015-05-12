#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/PluginManager.h"

using Neutron::Utility::PluginManager;

namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE NeutronSystem
		{
		public:
			PluginManager pluginManager;

			NeutronSystem();
			virtual ~NeutronSystem();

			boolean init( const char* path = 0 );
			void release();
		};

		inline NEUTRON_CORE NeutronSystem getSystem();
	};
}