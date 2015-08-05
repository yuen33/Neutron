#include "Resource.h"
#include "Device.h"

namespace Neutron
{
	namespace Engine
	{
		Resource::Resource( Device* owner )
			: resourceType( RT_Unknown )
			, owner( owner )
		{
		}

		Resource::~Resource()
		{
		}

		void Resource::deleteMethod( RCObject* object )
		{
			//assert( owner );
			if( owner )
			{
				release();
				delete static_cast<Resource*>( object );
			}
			else
			{
				RCObject::deleteMethod( object );
			}
		}
	}
}