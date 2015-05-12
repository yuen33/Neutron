#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronDevice.h"
#include "NeutronRenderDefine.h"

using Neutron::System::NeutronDevice;

namespace Neutron
{
	namespace Render
	{
		class NEUTRON_CORE RenderDevice : public NeutronDevice
		{
		public:
			RenderDevice();
			virtual ~RenderDevice();

			virtual boolean init() = 0;
			virtual void release() = 0;

			// pipeline
			virtual PipelinePtr createPipeline() = 0;

			// render window
			virtual RenderWindowPtr createRenderWindow() = 0;

			// buffer
			virtual BufferPtr createBuffer( int bufferType, int accessHint, Size stride, const ElementInitData* initData ) = 0;
			virtual BufferPtr createBuffer( int bufferType, int accessHint, Size stride, Size size ) = 0;

			// texture 1d
			virtual Texture1DPtr createTexture1D( int width, uint64 format, int mips, int arrayCount, int accessHint, const ElementInitData* initData ) = 0;
			virtual Texture1DPtr createTexture1D( ImagePtr image, int sampleCount, int sampleQuality, int accessHint ) = 0;

			// texture 2d
			virtual Texture2DPtr createTexture2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQualilty, int accessHint, const ElementInitData* initData ) = 0;
			virtual Texture2DPtr createTexture2D( ImagePtr image, int sampleCount, int sampleQuality, int accessHint ) = 0;
			virtual Texture2DPtr createTexture2D( RenderWindowPtr renderWindow ) = 0;

			// texture 3d
			virtual Texture3DPtr createTexture3D( int width, int height, int depth, uint64 format, int mips, int accessHint, const ElementInitData* initData ) = 0;
			virtual Texture3DPtr createTexture3D( ImagePtr image, int sampleCount, int sampleQuality, int accessHint ) = 0;
			
			// texture cube
			virtual TextureCube createTextureCube( int width, int height, uint64 format, int mips, int cubeCount, int32 sampleCount, int sampleQuality, int accessHint, const ElementInitData* initData ) = 0;
			virtual TextureCube createTextureCube( ImagePtr image, int sampleCount, int sampleQuality, int accessHint ) = 0;

			// sampler
			virtual SamplerPtr createSampler( int filterType, int addressModeU, int addressModeV, int addressModeW, float mipLODBias, int maxAnisotropy, int comparisionFunction, float4 borderColor, float minLOD, float maxLOD ) = 0;
			
			// shader
			virtual Shader* createShader( int shaderType, const char* code, Size size, const char* entryName, const char* include, const char* inlcudePath ) = 0;
		};
	}
}