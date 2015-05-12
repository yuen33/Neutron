#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/RCPtr.h"
#include "NeutronDevice.h"

using Neutron::Utility::RCObject;

namespace Neutron
{
	namespace System
	{
		class NeutronDevice;
		class NEUTRON_CORE NeutronResource : public RCObject
		{
			NeutronDevice* owner;

		protected:
			void deleteMethod( RCObject* object )
			{
				if( object )
				{
					owner->destroyResource( static_cast<NeutronResource*>( object ) );
				}
			}

		public:
			NeutronResource( NeutronDevice* owner );
			virtual ~NeutronResource();
		};
	}
}