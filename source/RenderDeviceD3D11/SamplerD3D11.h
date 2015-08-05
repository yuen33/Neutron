#include "NeutronSystem/Sampler.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class SamplerD3D11 : public Sampler
			{
			public:
				static SamplerPtr createSampler( Device* owner );
				SamplerD3D11( Device* owner );
				virtual ~SamplerD3D11();

				virtual void release();
			};
		}
	}
}