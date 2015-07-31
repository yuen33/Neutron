#pragma once

#include "NeutronSystemCommon.h"
#include "ProcessingUnit.h"

using Neutron::System::Device;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Renderer : public ProcessingUnit
			{
			public:
				Renderer( Device* owner );
				virtual ~Renderer();
			};
		}
	}
}