#pragma once

#include "NeutronSystem/Renderer.h"
#include <dxgi.h>

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class RendererD3D11 : public Renderer
			{
				PinPtr					window;
				Array<IDXGISwapChain*>	swapchains;

			public:
				static ProcessingUnitPtr createRenderer( Device* owner );
				RendererD3D11( Device* owner );
				virtual ~RendererD3D11();

				virtual boolean init();
				virtual void release() override;
				
				virtual boolean assembleUnit();
				virtual boolean updateUnit();

				void swap( HWND handle );
			};
		}
	}
}