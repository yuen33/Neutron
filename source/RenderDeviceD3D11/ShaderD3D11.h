#include "NeutronSystem/Shader.h"

using Neutron::Engine::Shader;

namespace Neutron
{
	namespace Engine
	{
		class ShaderD3D11 : public Shader
		{
			ShaderD3D11( Engine::Device* owner );
			virtual ~ShaderD3D11();
		};
	}
}