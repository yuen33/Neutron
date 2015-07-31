#include "RenderDeviceD3D11.h"
#include "NeutronSystem/Resource.h"
#include "NeutronSystem/Log.h"
#include "NeutronSystem/Image.h"
#include "NeutronSystem/NeutronEngine.h"

#include "InputStreamD3D11.h"
#include "BufferD3D11.h"
#include "TextureD3D11.h"
#include "SamplerD3D11.h"
#include "ShaderD3D11.h"

#include <d3d11.h>

using namespace Neutron::Engine;

namespace Neutron
{
	namespace System
	{
		RenderDeviceD3D11::RenderDeviceD3D11( NeutronPlugin* owner )
			: RenderDevice( owner )
		{
			enumerator.enumerate();
			enumerator.printDeviceInfo();
		}

		RenderDeviceD3D11::~RenderDeviceD3D11()
		{
		}

		void RenderDeviceD3D11::registerProducts()
		{
			NeutronEngine& engine = Neutron::Engine::getEngine();
			engine.getResourceManager().registerResource( "InputStream.D3D11", Engine::RT_InputStream, this );
			engine.getResourceManager().registerResource( "Buffer.D3D11", Engine::RT_InputStream, this );
			engine.getResourceManager().registerResource( "Texture.D3D11", Engine::RT_InputStream, this );
			engine.getResourceManager().registerResource( "Sampler.D3D11", Engine::RT_Sampler, this );
			engine.getResourceManager().registerResource( "Shader.D3D11", Engine::RT_Sampler, this );
		}

		void RenderDeviceD3D11::unregisterProducts()
		{
			NeutronEngine& engine = Neutron::Engine::getEngine();
			engine.getResourceManager().unregisterResource( "InputStream.D3D11" );
			engine.getResourceManager().unregisterResource( "Buffer.D3D11" );
			engine.getResourceManager().unregisterResource( "Texture.D3D11" );
			engine.getResourceManager().unregisterResource( "Sampler.D3D11" );
			engine.getResourceManager().unregisterResource( "Shader.D3D11" );
		}

		boolean RenderDeviceD3D11::init()
		{
			int desktopAdapterIndex = enumerator.getDesktopAdapterIndex();
			if( desktopAdapterIndex < 0 )
			{
				desktopAdapterIndex = 0;
			}

			IDXGIFactory* factory = 0;
			HRESULT hr = CreateDXGIFactory( __uuidof( IDXGIFactory ), (void**)&factory );
			if( FAILED( hr ) )
			{
				return false;
			}

			IDXGIAdapter* adapter = 0;
			hr = factory->EnumAdapters( desktopAdapterIndex, &adapter );
			if( FAILED( hr ) )
			{
				factory->Release();
				return false;
			}

			const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
			D3D_FEATURE_LEVEL selectedFeatureLevel;
			ID3D11Device* d3d = 0;
			ID3D11DeviceContext* d3dDC = 0;
			hr = D3D11CreateDevice( adapter, D3D_DRIVER_TYPE_UNKNOWN, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &d3d, &selectedFeatureLevel, &d3dDC );
			if( FAILED( hr ) )
			{
				adapter->Release();
				factory->Release();
			}

			this->dxgiFactory = factory;
			this->dxgiAdapter = adapter;
			this->d3dDevice = d3d;
			this->d3dContext = d3dDC;

			return true;
		}

		void RenderDeviceD3D11::release()
		{
			if( d3dContext )
			{
				d3dContext->Release();
			}

			if( d3dDevice )
			{
				d3dDevice->Release();
			}

			if( dxgiAdapter )
			{
				dxgiAdapter->Release();
			}

			if( dxgiFactory )
			{
				dxgiFactory->Release();
			}
		}

		InputStreamPtr RenderDeviceD3D11::createInputStream()
		{
			return InputStreamPtr::null;
		}

		BufferPtr RenderDeviceD3D11::createBuffer()
		{
			return BufferPtr::null;
		}

		TexturePtr RenderDeviceD3D11::createTexture1D( int width, uint64 format, int mips, int arraySize, int accessHint, Texture::InitData const* initData )
		{
			TexturePtr texture = TextureD3D11::createTexture( this );
			if( !texture.isNull() )
			{
				TextureD3D11* tex = static_cast<TextureD3D11*>( texture.get() );
				if( tex->init1D( width, format, mips, arraySize, accessHint, initData ) )
				{
					return texture;
				}
			}

			return TexturePtr::null;
		}

		TexturePtr RenderDeviceD3D11::createTexture2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData )
		{
			TexturePtr texture = TextureD3D11::createTexture( this );
			if( !texture.isNull() )
			{
				TextureD3D11* tex = static_cast<TextureD3D11*>( texture.get() );
				if( tex->init2D( width, height, format, mips, arraySize, sampleCount, sampleQuality, accessHint, initData ) )
				{
					return texture;
				}
			}

			return TexturePtr::null;
		}

		TexturePtr RenderDeviceD3D11::createTexture3D( int width, int height, int depth, uint64 format, int mips, int accessHint, Texture::InitData const* initData )
		{
			TexturePtr texture = TextureD3D11::createTexture( this );
			if( !texture.isNull() )
			{
				TextureD3D11* tex = static_cast<TextureD3D11*>( texture.get() );
				if( tex->init3D( width, height, height, format, mips, accessHint, initData ) )
				{
					return texture;
				}
			}

			return TexturePtr::null;
		}

		TexturePtr RenderDeviceD3D11::createTextureCube( int width, int height, uint64 format, int mips, int numOfCubes, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData )
		{
			TexturePtr texture = TextureD3D11::createTexture( this );
			if( !texture.isNull() )
			{
				TextureD3D11* tex = static_cast<TextureD3D11*>( texture.get() );
				if( tex->initCube( width, height, format, mips, numOfCubes, sampleCount, sampleQuality, accessHint, initData ) )
				{
					return texture;
				}
			}

			return TexturePtr::null;
		}

		TexturePtr RenderDeviceD3D11::createTextureFromImage( ImagePtr image, uint32 sampleCount, uint32 sampleQuality, uint32 accessHint )
		{
			TexturePtr texture = TextureD3D11::createTexture( this );
			if( !texture.isNull() )
			{
				TextureD3D11* tex = static_cast<TextureD3D11*>( texture.get() );
				if( tex->initFromImage( image, sampleCount, sampleQuality, accessHint ) )
				{
					return texture;
				}
			}

			return TexturePtr::null;
		}

		SamplerPtr RenderDeviceD3D11::createSampler()
		{
			return SamplerPtr::null;
		}

		ShaderPtr RenderDeviceD3D11::createShader()
		{
			return ShaderPtr::null;
		}
	}
}