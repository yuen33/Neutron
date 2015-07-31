#include "NeutronSystem/Sampler.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class SamplerD3D11 : public Sampler
			{
				SamplerD3D11( Engine::Device* owner );
				virtual ~SamplerD3D11();
			};
		}
	}
}