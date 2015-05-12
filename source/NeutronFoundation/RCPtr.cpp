#include "RCPtr.h"

namespace Neutron
{
	namespace Utility
	{
		RCObject::RCObject()
			:counter( 0 )
		{
		}
		
		RCObject::~RCObject()
		{
			removeReference();
		}
	}
}