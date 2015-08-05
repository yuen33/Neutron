#pragma once

#include "Device.h"

// resources
using Neutron::Engine::ImagePtr;
using Neutron::Engine::Render::RenderablePtr;

// modules
using Neutron::Engine::ProcessingModulePtr;
using Neutron::Engine::WindowPtr;


namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE SystemDevice : public Device
		{
		public:
			SystemDevice( NeutronPlugin* owner );
			virtual ~SystemDevice();

			boolean init();
			void release();

			// resources
			inline ImagePtr createImage1D( int width, uint64 format, int mips, int arraySize );
			inline ImagePtr createImage2D( int width, int height, uint64 format, int mips, int arraySize );
			inline ImagePtr createImage3D( int width, int height, int depth, uint64 format, int mips );
			inline ImagePtr createImageCube( int width, int height, uint64 format, int mips, int numOfCubes );
			inline ImagePtr createImageFromFile( const char* path );
			inline RenderablePtr createRenderable();

			// modules
			inline ProcessingModulePtr createProcessingModule();
			inline WindowPtr createWindow( int width, int height, const char* title, boolean fullscreen );
		};
	}
}