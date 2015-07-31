#include "NeutronSystem/Shader.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class ShaderD3D11 : public Shader
			{
				ShaderD3D11( Engine::Device* owner );
				virtual ~ShaderD3D11();
			};
		}
	}
}