#include "RenderDevice.h"

namespace Neutron
{
	namespace System
	{
		RenderDevice::RenderDevice( NeutronPlugin* owner )
			: Device( owner )
		{
			deviceType = DT_RenderDevice;
		}
		
		RenderDevice::~RenderDevice()
		{
		}
	}
}