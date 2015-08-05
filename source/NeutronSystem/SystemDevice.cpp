#include "SystemDevice.h"
#include "NeutronEngine.h"
#include "NeutronFoundation/FilePath.h"
#include "Image.h"
#include "FileJPEG.h"
#include "Renderable.h"
#include "ProcessingUnit.h"
#include "ProcessingModule.h"
#include "Window.h"

// resources
using Neutron::Engine::Image;
using Neutron::Utility::FilePath;
using Neutron::System::File::FileJPEG;
using Neutron::Engine::Render::Renderable;

// modules
using Neutron::Engine::ProcessingUnitPtr;
using Neutron::Engine::ProcessingModule;
using Neutron::Engine::Window;

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

			Engine::getEngine().getProcessingUnitManager().registerProcessingUnit( "Module", Engine::PUT_Module, this );
			Engine::getEngine().getProcessingUnitManager().registerProcessingUnit( "Window", Engine::PUT_Window, this );
			return true;
		}

		void SystemDevice::release()
		{
			Engine::getEngine().getResourceManager().unregisterResource( "Image" );
			Engine::getEngine().getResourceManager().unregisterResource( "Renderable" );

			Engine::getEngine().getProcessingUnitManager().unregisterProcessingUnit( "Module" );
			Engine::getEngine().getProcessingUnitManager().unregisterProcessingUnit( "Window" );
		}

		ImagePtr SystemDevice::createImage1D( int width, uint64 format, int mips, int arraySize )
		{
			ImagePtr image = Image::createImage( this );
			if( !image.isNull() && image->init1D( width, format, mips, arraySize ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr SystemDevice::createImage2D( int width, int height, uint64 format, int mips, int arraySize )
		{
			ImagePtr image = Image::createImage( this );
			if( !image.isNull() && image->init2D( width, height, format, mips, arraySize ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr SystemDevice::createImage3D( int width, int height, int depth, uint64 format, int mips )
		{
			ImagePtr image = Image::createImage( this );
			if( !image.isNull() && image->init3D( width, height, depth, format, mips ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr SystemDevice::createImageCube( int width, int height, uint64 format, int mips, int numOfCubes )
		{
			ImagePtr image = Image::createImage( this );
			if( !image.isNull() && image->initCube( width, height, format, mips, numOfCubes ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr SystemDevice::createImageFromFile( const char* path )
		{
			String ext = FilePath::getExt( path );
			ext.lower();
			if( ext == "jpg" || ext == "jpeg" )
			{
				return System::File::FileJPEG::load( path );
			}

			return ImagePtr::null;
		}

		RenderablePtr SystemDevice::createRenderable()
		{
			RenderablePtr renderable = Renderable::create( this );
			return renderable;
		}

		ProcessingUnitPtr SystemDevice::createProcessingModule()
		{
			ProcessingUnitPtr module = ProcessingModule::createProcessingUnitModule( this );
			return module;
		}

		ProcessingUnitPtr SystemDevice::createWindow( int width, int height, const char* title, boolean fullscreen )
		{
			ProcessingUnitPtr window = Window::create( this );
			if( !window.isNull() && staticCast<Window>( window )->init( width, height, title, fullscreen ) )
			{
				return window;
			}

			return ProcessingUnitPtr::null;
		}
	}
}