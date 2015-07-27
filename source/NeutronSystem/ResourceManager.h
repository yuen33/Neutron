#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/Stream.h"


using Neutron::System::Device;

namespace Neutron
{
	namespace Engine
	{
		class ResourceManager
		{
			struct ResourceInfo
			{
				int resourceType;
				String name;
				Device* device;

				ResourceInfo()
				{
				}

				ResourceInfo( int resourceType, const char* name, Device* plugin )
					: resourceType( resourceType )
					, name( name )
					, device( device )
				{
				}
			};

		public:
			ResourceManager();
			virtual ~ResourceManager();

			void registerResource( const char* name, int resourceType, Device* device );
			void unregisterResource( const char* name );

			ImagePtr		createImage();
			InputStreamPtr	createInputStream();
			BufferPtr		createBuffer();
			TexturePtr		createTexture();
			SamplerPtr		createSampler();
			ShaderPtr		createShader();
			ViewportPtr		createViewport();
			WindowPtr		createWindow();
		};
	}
}