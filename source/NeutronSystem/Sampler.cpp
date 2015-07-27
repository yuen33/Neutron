#include "Sampler.h"

namespace Neutron
{
	namespace Engine
	{
		Sampler::Sampler( Device* owner )
			: Resource( owner )
		{
			resourceType = RT_Sampler;
		}

		Sampler::~Sampler()
		{
		}
	}
}