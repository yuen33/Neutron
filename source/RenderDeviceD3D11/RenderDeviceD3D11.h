#pragma once

#include "NeutronSystem/RenderDevice.h"
#include "RenderDeviceEnumerator.h"
#include <dxgi.h>
#include <d3d11.h>

namespace Neutron
{
	namespace System
	{
		class RenderDeviceD3D11 : public RenderDevice
		{
		public:

			// access hint
			enum : int
			{
				AH_Unknown = 0,
				AH_CPU_Read = 1 << 0,
				AH_CPU_Write = 1 << 1,
				AH_GPU_Read = 1 << 2,
				AH_GPU_Write = 1 << 3,
				AH_GPU_Unordered = 1 << 4,
				AH_GenerateMips = 1 << 5,
				AH_Immutable = 1 << 6,
				AH_Raw = 1 << 7,
				AH_Append = 1 << 8,
				AH_Counter = 1 << 9,
				AH_DrawInDirectArgs = 1 << 10
			};

			RenderDeviceEnumerator		enumerator;
			IDXGIFactory*				dxgiFactory;
			IDXGIAdapter*				dxgiAdapter;
			ID3D11Device*				d3dDevice;
			ID3D11DeviceContext*		d3dContext;

			void registerProducts();
			void unregisterProducts();

		public:
			RenderDeviceD3D11( NeutronPlugin* owner );
			virtual ~RenderDeviceD3D11();

			virtual boolean init();
			void release();

			virtual InputStreamPtr createInputStream();
			virtual BufferPtr createBuffer();

			virtual TexturePtr createTexture1D( int width, uint64 format, int mips, int arraySize, int accessHint, Texture::InitData const* initData );
			virtual TexturePtr createTexture2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData );
			virtual TexturePtr createTexture3D( int width, int height, int depth, uint64 format, int mips, int accessHint, Texture::InitData const* initData );
			virtual TexturePtr createTextureCube( int width, int height, uint64 format, int mips, int numCubes, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData );
			virtual TexturePtr createTextureFromImage( ImagePtr image, uint32 sampleCount, uint32 sampleQuality, uint32 accessHint );

			virtual SamplerPtr createSampler();
			virtual ShaderPtr createShader();

			inline IDXGIFactory* getDXGIFactory() { return dxgiFactory; }
			inline IDXGIAdapter* getDXGIAdapter() { return dxgiAdapter; }
			inline ID3D11Device* getD3DDevice() { return d3dDevice; }
			inline ID3D11DeviceContext* getD3DContext() { return d3dContext; }

			inline virtual const wchar* getDesktopName() const { return enumerator.getDesktopOutpuName(); }
			inline virtual int getDesktopWidth() const { return enumerator.getDesktopWidth(); }
			inline virtual int getDesktopHeight() const { return enumerator.getDesktopHeight(); }
			inline virtual int getDesktopAdapterIndex() const { return enumerator.getDesktopAdapterIndex(); }
		};
	}
}