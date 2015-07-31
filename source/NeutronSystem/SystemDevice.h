#pragma once

#include "Device.h"

using Neutron::Engine::ImagePtr;
using Neutron::Engine::WindowPtr;
using Neutron::Engine::Render::RenderablePtr;

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

			inline ImagePtr create1D( int width, uint64 format, int mips, int arraySize );
			inline ImagePtr create2D( int width, int height, uint64 format, int mips, int arraySize );
			inline ImagePtr create3D( int width, int height, int depth, uint64 format, int mips );
			inline ImagePtr createCube( int width, int height, uint64 format, int mips, int numOfCubes );

			inline RenderablePtr createRenderable();

			inline WindowPtr createWindow( int width, int height, const char* title, boolean fullscreen );
		};
	}
}