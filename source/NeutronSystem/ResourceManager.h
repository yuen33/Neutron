#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/String.h"
#include "NeutronFoundation/HashMap.h"
#include "Texture.h"

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
			inline ImagePtr createImageFromFile( const char* path );

			Render::InputStreamPtr createInputStream();

			Render::BufferPtr createBuffer();

			Render::TexturePtr createTexture1D( int width, uint64 format, int mips, int arraySize, int accessHint, Render::Texture::InitData const* initData );
			Render::TexturePtr createTexture2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQuality, int accessHint, Render::Texture::InitData const* initData );
			Render::TexturePtr createTexture3D( int width, int height, int depth, uint64 format, int mips, int accessHint, Render::Texture::InitData const* initData );
			Render::TexturePtr createTextureCube( int width, int height, uint64 format, int mips, int numCubes, int sampleCount, int sampleQuality, int accessHint, Render::Texture::InitData const* initData );
			Render::TexturePtr createTextureFromImage( ImagePtr image, uint32 sampleCount, uint32 sampleQuality, uint32 accessHint );

			Render::SamplerPtr createSampler();

			Render::ShaderPtr createVertexShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath );
			Render::ShaderPtr createHullShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath );
			Render::ShaderPtr createDomainShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath );
			Render::ShaderPtr createGeometryShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath );
			Render::ShaderPtr createPixelShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath );
			Render::ShaderPtr createComputeShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath );
		};
	}
}