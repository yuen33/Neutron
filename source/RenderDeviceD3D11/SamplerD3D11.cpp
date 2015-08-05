#include "SamplerD3D11.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			SamplerPtr SamplerD3D11::createSampler( Device* owner )
			{
				return SamplerPtr( new SamplerD3D11( owner ) );
			}

			SamplerD3D11::SamplerD3D11( Device* owner )
				: Sampler( owner )
			{
			}

			SamplerD3D11::~SamplerD3D11()
			{
			}

			void SamplerD3D11::release()
			{
			}
		}
	}
}