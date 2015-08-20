#include "NeutronSystem/Sampler.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class SamplerD3D11 : public Sampler
			{
				ID3D11SamplerState*		d3dSamplerState;

			public:
				static SamplerPtr createSampler( Device* owner );
				SamplerD3D11( Device* owner );
				virtual ~SamplerD3D11();

				boolean init( int filterType, int addressModeU, int addressModeV, int addressModeW, float mipLoadBias, int maxAnisotropy, int comparisonFunction, float4 borderColor, float minLod, float maxLod );
				void release();

				virtual void release();
			};
		}
	}
}