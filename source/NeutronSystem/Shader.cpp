#include "Shader.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			ShaderPtr Shader::createShader( Device* owner )
			{
				return ShaderPtr( new Shader( owner ) );
			}

			Shader::Shader( Device* owner )
				: Resource( owner )
				, shaderType( ST_Unknown ) 
			{
				resourceType = RT_Shader;
			}

			Shader::~Shader()
			{
			}
		}
	}
}