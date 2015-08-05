#include "RendererD3D11.h"
#include "NeutronSystem/Pin.h"
#include "NeutronSystem/Window.h"
#include "RenderDeviceD3D11/RenderDeviceD3D11.h"
#include "NeutronSystem/PixelFormat.h"
#include "MapperD3D11.h"

using Neutron::System::RenderDeviceD3D11;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			ProcessingUnitPtr RendererD3D11::createRenderer( Device* owner )
			{
				return ProcessingUnitPtr( new RendererD3D11( owner ) );
			}

			RendererD3D11::RendererD3D11( Device* owner )
				: Renderer( owner )
			{
			}

			RendererD3D11::~RendererD3D11()
			{
			}

			boolean RendererD3D11::init()
			{
				window = ProcessingUnitPin::createPin( Pin::PD_Output );
				registerPin( "window", staticCast<Pin>( window ) );

				return true;
			} 

			void RendererD3D11::release()
			{
				window = 0;

				for( int i = 0; i < swapchains.getCount(); ++i )
				{
					if( swapchains[i] )
					{
						swapchains[i]->Release();
					}
				}
				swapchains.clear();

				unregisterPin( "window" );
			}

			boolean RendererD3D11::assembleUnit()
			{
				ProcessingUnitPtr windowUnit = ProcessingUnitPtr::null;
				window->getData( windowUnit );
				if( !windowUnit.isNull() )
				{
					WindowPtr wnd = staticCast<Window>( windowUnit );
					RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
					IDXGIFactory* dxgiFactory = rd->getDXGIFactory();
					
					DXGI_SWAP_CHAIN_DESC desc;
					desc.BufferCount = 1;
					desc.BufferDesc.Width = wnd->getWidth();
					desc.BufferDesc.Height = wnd->getHeight();
					desc.BufferDesc.Format = MapperD3D11::mapPixelFormat( Render::PF_RGBA8UN );
					desc.BufferDesc.RefreshRate.Numerator = 60;
					desc.BufferDesc.RefreshRate.Denominator = 1;
					desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
					desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
					desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
					desc.OutputWindow = (HWND)wnd->getHandle();
					desc.SampleDesc.Count = 1;
					desc.SampleDesc.Quality = 0;
					desc.Windowed = !wnd->isFullscreen();
					desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
					desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

					IDXGISwapChain* sc = 0;
					HRESULT hr = dxgiFactory->CreateSwapChain( rd->getD3DDevice(), &desc, &sc );
					if( SUCCEEDED( hr ) )
					{
						swapchains.add( sc );
						wnd->setSwapChain( sc );
						return true;
					}
				}
				
				return false;
			}

			boolean RendererD3D11::updateUnit()
			{
				ProcessingUnitPtr windowUnit = ProcessingUnitPtr::null;
				window->getData( windowUnit );
				if( !windowUnit.isNull() )
				{
					return windowUnit->updateUnit();
				}

				return false;
			}
		}
	}
}