#pragma once

#include "Device.h"

namespace Neutron
{
	namespace System
	{
		class SystemDevice : public Device
		{
		public:
			SystemDevice();
			virtual ~SystemDevice();
		};
	}
}