#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/String.h"
#include "NeutronFoundation/HashMap.h"

using Neutron::Container::String;
using Neutron::Container::HashMap;
using Neutron::System::Device;

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE ResourceManager
		{
			struct ResourceInfo
			{
				int resourceType;
				String name;
				Device* device;

				ResourceInfo()
				{
				}

				ResourceInfo( int resourceType, const char* name, Device* device )
					: resourceType( resourceType )
					, name( name )
					, device( device )
				{
				}
			};

			HashMap<uint32, ResourceInfo*>			nameIndex;
			HashMap<int, Array<ResourceInfo*> >		typeIndex;
			HashMap<int, Array<Resource*> >			resources;

			ResourceInfo* findInfoByResourceType( int resourceType );

		public:
			ResourceManager();
			virtual ~ResourceManager();

			void registerResource( const char* name, int resourceType, Device* device );
			void unregisterResource( const char* name );

			// image
			inline ImagePtr createImage1D( int width, uint64 format, int mips, int arraySize );
			inline ImagePtr createImage2D( int width, int height, uint64 format, int mips, int arraySize );
			inline ImagePtr createImage3D( int width, int height, int depth, uint64 format, int mips );
			inline ImagePtr createImageCube( int width, int height, uint64 format, int mips, int numOfCubes );

			Render::InputStreamPtr createInputStream();
			Render::BufferPtr createBuffer();
			Render::TexturePtr createTexture();
			Render::SamplerPtr createSampler();
			Render::ShaderPtr createShader();
		};
	}
}