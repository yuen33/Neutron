#include "Window.h"

namespace Neutron
{
	namespace Engine
	{
		Window::Window( Device* owner )
			: Resource( owner )
		{
			resourceType = RT_Window;
		}

		Window::~Window()
		{
		}
	}
}