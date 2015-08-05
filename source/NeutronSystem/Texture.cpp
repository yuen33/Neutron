#include "Texture.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			Texture::Texture( Device* owner )
				: Resource( owner )
				, textureType( TT_Unknown )
			{
				resourceType = RT_Texture;
			}

			Texture::~Texture()
			{
			}
		}
	}
}