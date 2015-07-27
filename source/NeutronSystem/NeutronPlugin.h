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
			struct Version
			{
				uint32 major;
				uint32 minor;
				uint32 revision;
				uint32 build;

				Version( uint32 major_, uint32 minor_, uint32 revision_, uint32 build_ )
					: major( major_ )
					, minor( minor_ )
					, revision( revision_ )
					, build( build_ )
				{
				}

				Version& operator=( const Version& rhs )
				{
					major = rhs.major;
					minor = rhs.minor;
					revision = rhs.revision;
					build = rhs.build;
				}
			};

		public:
			NeutronPlugin();
			virtual ~NeutronPlugin();

			virtual boolean init() = 0;
			virtual void release() = 0;

			virtual Device* createDevice( const char* name ) = 0;
			virtual void destroyDevice( Device* device ) = 0;

			virtual const char* getVendorName() = 0;
			virtual Version getVersion() = 0;
		};
	}
}