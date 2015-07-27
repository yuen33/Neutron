#include "Texture.h"

namespace Neutron
{
	namespace Engine
	{
		Texture::Texture( Device* owner )
			: Resource( owner )
		{
			resourceType = RT_Texture;
		}

		Texture::~Texture()
		{
		}
	}
}