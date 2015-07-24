#pragma once

#include "NeutronFoundation/RCPtr.h"

using Neutron::Utility::RCObject;
using Neutron::Utility::RCPtr;

namespace Neutron
{
	namespace Engine
	{
		// framework
		class DataFrame;
		class DataStream;
		class Pin;
		class Variable;
		class VPU;

		typedef RCPtr<DataFrame>		DataFramePtr;
		typedef RCPtr<DataStream>		DataStreamPtr;
		typedef RCPtr<Pin>				PinPtr;
		typedef RCPtr<Variable>			VariablePtr;
		typedef RCPtr<VPU>				VPUPtr;

		// devices
		class Device;
		class RenderDevice;

		typedef RCPtr<RenderDevice>		RenderDevicePtr;

		// resources
		class Resource;
		class Image;
		class InputStream;
		class Buffer;
		class Texture;
		class Sampler;
		class Shader;
		class Viewport;
		class Window;

		typedef RCPtr<Image>			ImagePtr;
		typedef RCPtr<InputStream>		InputStreamPtr;
		typedef RCPtr<Buffer>			BufferPtr;
		typedef RCPtr<Texture>			TexturePtr;
		typedef RCPtr<Sampler>			SamplerPtr;
		typedef RCPtr<Shader>			ShaderPtr;
		typedef RCPtr<Viewport>			ViewportPtr;
		typedef RCPtr<Window>			WindowPtr;
	}
}