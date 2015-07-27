#include "NeutronSystem/InputStream.h"

using Neutron::Engine::InputStream;

namespace Neutron
{
	namespace Engine
	{
		class InputStreamD3D11 : public InputStream
		{
			InputStreamD3D11( Engine::Device* owner );
			virtual ~InputStreamD3D11();
		};
	}
}