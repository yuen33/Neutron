#include "NeutronSystem/InputStream.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class InputStreamD3D11 : public InputStream
			{
				InputStreamD3D11( Engine::Device* owner );
				virtual ~InputStreamD3D11();
			};
		}
	}
}