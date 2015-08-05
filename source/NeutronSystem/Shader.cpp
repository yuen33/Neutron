#include "Shader.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
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