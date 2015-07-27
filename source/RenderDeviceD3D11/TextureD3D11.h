#include "NeutronSystem/Texture.h"

using Neutron::Engine::Texture;

namespace Neutron
{
	namespace Engine
	{
		class TextureD3D11 : public Texture
		{
			TextureD3D11( Engine::Device* owner );
			virtual ~TextureD3D11();
		};
	}
}