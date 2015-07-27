#include "Device.h"
#include "NeutronPlugin.h"

namespace Neutron
{
	namespace System
	{
		Device::Device( NeutronPlugin* owner )
			: deviceType( DT_Unknown )
			, owner( owner )
		{
		}

		Device::~Device()
		{
		}

		void Device::deleteMethod( RCObject* object )
		{
			assert( owner );
			if( owner )
			{
				owner->destroyDevice( this );
			}
			else
			{
				RCObject::deleteMethod( object );
			}
		}

		boolean Device::init()
		{
			return false;
		}

		void Device::release()
		{
		}

		void Device::onPluginRelease()
		{
		}
	}
}