#include "ResourceManager.h"
#include "NeutronFoundation/Hash.h"
#include "SystemDevice.h"
#include "RenderDevice.h"
#include "Image.h"
#include "InputStream.h"
#include "Buffer.h"
#include "Texture.h"
#include "Sampler.h"
#include "Shader.h"

namespace Neutron
{
	namespace Engine
	{
		ResourceManager::ResourceManager()
		{
		}

		ResourceManager::~ResourceManager()
		{
		}

		void ResourceManager::registerResource( const char* name, int resourceType, Device* device )
		{
			ResourceInfo* newInfo = new ResourceInfo( resourceType, name, device );
			nameIndex.add( Math::Hash::DJB32( name ), newInfo );
			HashMap<int, Array<ResourceInfo*> >::Iterator itTypeIndex = typeIndex.find( resourceType );
			if( itTypeIndex != typeIndex.end() )
			{
				itTypeIndex.value().add( newInfo );
			}
			else
			{
				Array<ResourceInfo*> newInfoArray;
				newInfoArray.add( newInfo );
				typeIndex.add( resourceType, newInfoArray );
			}
		}

		void ResourceManager::unregisterResource( const char* name )
		{
			// find name
			HashMap<uint32, ResourceInfo*>::Iterator itNameIndex = nameIndex.find( Math::Hash::DJB32( name ) );
			if( itNameIndex != nameIndex.end() )
			{
				// find type
				int resourceType = itNameIndex.value()->resourceType;
				HashMap<int, Array<ResourceInfo*> >::Iterator itTypeIndex = typeIndex.find( resourceType );
				if( itTypeIndex != typeIndex.end() )
				{
					// search array
					Array<ResourceInfo*>& infoArray = itTypeIndex.value();
					int removeIndex = -1;
					for( int i = 0; i < infoArray.getCount(); ++i )
					{
						if( infoArray[i] == itNameIndex.value() )
						{
							removeIndex = i;
							break;
						}
					}

					// remove from array
					if( removeIndex >= 0 )
					{
						infoArray.removeAtFast( removeIndex );
					}
				}

				// delete info
				delete itNameIndex.value();
				nameIndex.remove( itNameIndex );
			}
		}

		ResourceManager::ResourceInfo* ResourceManager::findInfoByResourceType( int resourceType )
		{
			HashMap<int, Array<ResourceInfo*> >::Iterator itTypeIndex = typeIndex.find( resourceType );
			if( itTypeIndex != typeIndex.end() )
			{
				return itTypeIndex.value()[0];
			}

			return 0;
		}

		ImagePtr ResourceManager::createImage1D( int width, uint64 format, int mips, int arraySize )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Image );
			if( info )
			{
				System::SystemDevice* device = static_cast<System::SystemDevice*>( info->device );
				if( device )
				{
					return device->createImage1D( width, format, mips, arraySize );
				}
			}

			return ImagePtr::null;
		}

		ImagePtr ResourceManager::createImage2D( int width, int height, uint64 format, int mips, int arraySize )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Image );
			if( info )
			{
				System::SystemDevice* device = static_cast<System::SystemDevice*>( info->device );
				if( device )
				{
					return device->createImage2D( width, height, format, mips, arraySize );
				}
			}

			return ImagePtr::null;
		}

		ImagePtr ResourceManager::createImage3D( int width, int height, int depth, uint64 format, int mips )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Image );
			if( info )
			{
				System::SystemDevice* device = static_cast<System::SystemDevice*>( info->device );
				if( device )
				{
					return device->createImage3D( width, height, depth, format, mips );
				}
			}

			return ImagePtr::null;
		}

		ImagePtr ResourceManager::createImageCube( int width, int height, uint64 format, int mips, int numOfCubes )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Image );
			if( info )
			{
				System::SystemDevice* device = static_cast<System::SystemDevice*>( info->device );
				if( device )
				{
					return device->createImageCube( width, height, format, mips, numOfCubes );
				}
			}

			return ImagePtr::null;
		}

		ImagePtr ResourceManager::createImageFromFile( const char* path )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Image );
			if( info )
			{
				System::SystemDevice* device = static_cast<System::SystemDevice*>( info->device );
				if( device )
				{
					return device->createImageFromFile( path );
				}
			}

			return ImagePtr::null;
		}

		Render::InputStreamPtr ResourceManager::createInputStream()
		{
			return Render::InputStreamPtr::null;
		}

		Render::BufferPtr ResourceManager::createBuffer()
		{
			return Render::BufferPtr::null;
		}

		Render::TexturePtr ResourceManager::createTexture1D( int width, uint64 format, int mips, int arraySize, int accessHint, Render::Texture::InitData const* initData )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Texture );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createTexture1D( width, format, mips, arraySize, accessHint, initData );
				}
			}

			return TexturePtr::null;
		}

		Render::TexturePtr ResourceManager::createTexture2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQuality, int accessHint, Render::Texture::InitData const* initData )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Texture );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createTexture2D( width, height, format, mips, arraySize, sampleCount, sampleQuality, accessHint, initData );
				}
			}

			return TexturePtr::null;
		}

		Render::TexturePtr ResourceManager::createTexture3D( int width, int height, int depth, uint64 format, int mips, int accessHint, Render::Texture::InitData const* initData )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Texture );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createTexture1D( width, format, depth, mips, accessHint, initData );
				}
			}

			return TexturePtr::null;
		}

		Render::TexturePtr ResourceManager::createTextureCube( int width, int height, uint64 format, int mips, int numCubes, int sampleCount, int sampleQuality, int accessHint, Render::Texture::InitData const* initData )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Texture );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createTextureCube( width, height, format, mips, numCubes, sampleCount, sampleQuality, accessHint, initData );
				}
			}

			return TexturePtr::null;
		}

		Render::TexturePtr ResourceManager::createTextureFromImage( ImagePtr image, uint32 sampleCount, uint32 sampleQuality, uint32 accessHint )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Texture );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createTextureFromImage( image, sampleCount, sampleQuality, accessHint );
				}
			}

			return TexturePtr::null;
		}

		Render::SamplerPtr ResourceManager::createSampler()
		{
			return Render::SamplerPtr::null;
		}

		Render::ShaderPtr ResourceManager::createVertexShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Shader );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createVertexShader( charCode, size, entry, include, includePath );
				}
			}

			return ShaderPtr::null;
		}

		Render::ShaderPtr ResourceManager::createHullShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Shader );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createHullShader( charCode, size, entry, include, includePath );
				}
			}

			return ShaderPtr::null;
		}

		Render::ShaderPtr ResourceManager::createDomainShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Shader );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createDomainShader( charCode, size, entry, include, includePath );
				}
			}

			return ShaderPtr::null;
		}

		Render::ShaderPtr ResourceManager::createGeometryShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Shader );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createGeometryShader( charCode, size, entry, include, includePath );
				}
			}

			return ShaderPtr::null;
		}

		Render::ShaderPtr ResourceManager::createPixelShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Shader );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createPixelShader( charCode, size, entry, include, includePath );
				}
			}

			return ShaderPtr::null;
		}

		Render::ShaderPtr ResourceManager::createComputeShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
		{
			ResourceInfo* info = findInfoByResourceType( RT_Shader );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createComputeShader( charCode, size, entry, include, includePath );
				}
			}

			return ShaderPtr::null;
		}
	}
}