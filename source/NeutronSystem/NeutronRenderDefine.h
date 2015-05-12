#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/RCPtr.h"

using Neutron::Utility::RCPtr;

namespace Neutron
{
	namespace Render
	{
		class RenderResource;
		class Pipeline;
		class RenderWindow;
		class Buffer;
		class Texture1D;
		class Texture2D;
		class Texture3D;
		class TextureCube;
		class Sampler;
		class Shader;
		class Image;

		typedef RCPtr<RenderResource>	RenderResourcePtr;
		typedef RCPtr<Pipeline>			PipelinePtr;
		typedef RCPtr<RenderWindow>		RenderWindowPtr;
		typedef RCPtr<Buffer>			BufferPtr;
		typedef RCPtr<Texture1D>		Texture1DPtr;
		typedef RCPtr<Texture2D>		Texture2DPtr;
		typedef RCPtr<Texture3D>		Texture3DPtr;
		typedef RCPtr<TextureCube>		TextureCubePtr;
		typedef RCPtr<Sampler>			SamplerPtr;
		typedef RCPtr<Shader>			ShaderPtr;
		typedef RCPtr<Image>			ImagePtr;

		// structs
		struct ElementInitData
		{
			const void* data;
			uint32		rowPitch;
			uint32		slicePitch;
		};
	}
}