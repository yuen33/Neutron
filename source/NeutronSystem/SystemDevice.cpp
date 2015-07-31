#include "SystemDevice.h"
#include "NeutronEngine.h"
#include "Image.h"
#include "Window.h"
#include "Renderable.h"

using Neutron::Engine::Image;
using Neutron::Engine::Window;
using Neutron::Engine::Render::Renderable;

namespace Neutron
{
	namespace System
	{
		SystemDevice::SystemDevice( NeutronPlugin* owner )
			: Device( owner )
		{
			deviceType = DT_SystemDevice;
		}

		SystemDevice::~SystemDevice()
		{
		}

		boolean SystemDevice::init()
		{
			Engine::getEngine().getResourceManager().registerResource( "Image", Engine::RT_Image, this );
			Engine::getEngine().getResourceManager().registerResource( "Renderable", Engine::RT_Renderable, this );

			Engine::getEngine().getProcessingUnitManager().registerProcessingUnit( "Window", Engine::PUT_Window, this );
			return true;
		}

		void SystemDevice::release()
		{
			Engine::getEngine().getResourceManager().unregisterResource( "Image" );
			Engine::getEngine().getResourceManager().unregisterResource( "Renderable" );

			Engine::getEngine().getProcessingUnitManager().unregisterProcessingUnit( "Window" );
		}

		ImagePtr SystemDevice::create1D( int width, uint64 format, int mips, int arraySize )
		{
			ImagePtr image = Image::create( this );
			if( !image.isNull() && image->init1D( width, format, mips, arraySize ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr SystemDevice::create2D( int width, int height, uint64 format, int mips, int arraySize )
		{
			ImagePtr image = Image::create( this );
			if( !image.isNull() && image->init2D( width, height, format, mips, arraySize ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr SystemDevice::create3D( int width, int height, int depth, uint64 format, int mips )
		{
			ImagePtr image = Image::create( this );
			if( !image.isNull() && image->init3D( width, height, depth, format, mips ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr SystemDevice::createCube( int width, int height, uint64 format, int mips, int numOfCubes )
		{
			ImagePtr image = Image::create( this );
			if( !image.isNull() && image->initCube( width, height, format, mips, numOfCubes ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		RenderablePtr SystemDevice::createRenderable()
		{
			RenderablePtr renderable = Renderable::create( this );
			return renderable;
		}

		WindowPtr SystemDevice::createWindow( int width, int height, const char* title, boolean fullscreen )
		{
			WindowPtr window = Window::create( this );
			if( !window.isNull() && window->init( width, height, title, fullscreen ) )
			{
				return window;
			}

			return WindowPtr::null;
		}
	}
}