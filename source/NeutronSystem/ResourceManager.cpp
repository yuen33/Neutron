#include "ResourceManager.h"
#include "NeutronFoundation/Hash.h"
#include "SystemDevice.h"
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
					return device->create1D( width, format, mips, arraySize );
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
					return device->create2D( width, height, format, mips, arraySize );
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
					return device->create3D( width, height, depth, format, mips );
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
					return device->createCube( width, height, format, mips, numOfCubes );
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

		Render::TexturePtr ResourceManager::createTexture()
		{
			return Render::TexturePtr::null;
		}

		Render::SamplerPtr ResourceManager::createSampler()
		{
			return Render::SamplerPtr::null;
		}

		Render::ShaderPtr ResourceManager::createShader()
		{
			return Render::ShaderPtr::null;
		}
	}
}