#pragma once

#include "Device.h"
#include "Texture.h"
#include "Buffer.h"

using namespace Neutron::Engine::Render;

using Neutron::Engine::ImagePtr;
using Neutron::Engine::Render::TexturePtr;

namespace Neutron
{
	namespace System
	{
		class NEUTRON_CORE RenderDevice : public Device
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

		public:
			RenderDevice( NeutronPlugin* owner );
			virtual ~RenderDevice();

			virtual InputStreamPtr createInputStream() = 0;
			virtual BufferPtr createBuffer() = 0;

			virtual TexturePtr createTexture1D( int width, uint64 format, int mips, int arraySize, int accessHint, Texture::InitData const* initData ) = 0;
			virtual TexturePtr createTexture2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData ) = 0;
			virtual TexturePtr createTexture3D( int width, int height, int depth, uint64 format, int mips, int accessHint, Texture::InitData const* initData ) = 0;
			virtual TexturePtr createTextureCube( int width, int height, uint64 format, int mips, int numCubes, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData ) = 0;
			virtual TexturePtr createTextureFromImage( ImagePtr image, uint32 sampleCount, uint32 sampleQuality, uint32 accessHint ) = 0;

			virtual SamplerPtr createSampler() = 0;

			virtual ShaderPtr createVertexShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath ) = 0;
			virtual ShaderPtr createHullShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath ) = 0;
			virtual ShaderPtr createDomainShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath ) = 0;
			virtual ShaderPtr createGeometryShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath ) = 0;
			virtual ShaderPtr createPixelShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath ) = 0;
			virtual ShaderPtr createComputeShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath ) = 0;

			virtual RendererPtr createRenderer() = 0;

			virtual const wchar* getDesktopName() const = 0;
			virtual int getDesktopWidth() const = 0;
			virtual int getDesktopHeight() const = 0;
			virtual int getDesktopAdapterIndex() const = 0;
		};
	}
}