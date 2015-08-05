#include "Renderer.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			Renderer::Renderer( Device* owner )
				: ProcessingUnit( owner )
			{
			}

			Renderer::~Renderer()
			{
			}

			boolean Renderer::init()
			{
				return true;
			}
		}
	}
}