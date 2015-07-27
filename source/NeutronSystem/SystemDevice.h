#pragma once

#include "Device.h"

namespace Neutron
{
	namespace System
	{
		class SystemDevice : public Device
		{
		public:
			SystemDevice( NeutronPlugin* owner );
			virtual ~SystemDevice();

			boolean init();
			void release();

			Engine::ImagePtr create1D( int width, uint64 format, int mips, int arraySize );
			Engine::ImagePtr create2D( int width, int height, uint64 format, int mips, int arraySize );
			Engine::ImagePtr create3D( int width, int height, int depth, uint64 format, int mips );
			Engine::ImagePtr createCube( int width, int height, uint64 format, int mips, int numOfCubes );

			void destroyResource( Engine::ResourcePtr resource );
		};
	}
}