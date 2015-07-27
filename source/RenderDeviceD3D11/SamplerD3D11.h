#include "NeutronSystem/Sampler.h"

using Neutron::Engine::Sampler;

namespace Neutron
{
	namespace Engine
	{
		class SamplerD3D11 : public Sampler
		{
			SamplerD3D11( Engine::Device* owner );
			virtual ~SamplerD3D11();
		};
	}
}