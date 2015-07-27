#include "NeutronSystem/Buffer.h"

using Neutron::Engine::Buffer;

namespace Neutron
{
	namespace Engine
	{
		class BufferD3D11 : public Buffer
		{
			BufferD3D11( Engine::Device* owner );
			virtual ~BufferD3D11();
		};
	}
}