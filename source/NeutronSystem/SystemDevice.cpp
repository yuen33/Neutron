#include "SystemDevice.h"
#include "Image.h"

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
			return true;
		}

		void SystemDevice::release()
		{
		}

		Engine::ImagePtr SystemDevice::create1D( int width, uint64 format, int mips, int arraySize )
		{
			return Engine::Image::create1D( width, format, mips, arraySize );
		}

		Engine::ImagePtr SystemDevice::create2D( int width, int height, uint64 format, int mips, int arraySize )
		{
			return Engine::Image::create2D( width, height, format, mips, arraySize );
		}

		Engine::ImagePtr SystemDevice::create3D( int width, int height, int depth, uint64 format, int mips )
		{
			return Engine::Image::create3D( width, height, depth, format, mips );
		}

		Engine::ImagePtr SystemDevice::createCube( int width, int height, uint64 format, int mips, int numOfCubes )
		{
			return Engine::Image::createCube( width, height, format, mips, numOfCubes );
		}
	}
}