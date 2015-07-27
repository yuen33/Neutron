#pragma once

#include "NeutronFoundation/RCPtr.h"
#include "NeutronFoundation/MessageBus.h"

using Neutron::Utility::RCObject;
using Neutron::Utility::RCPtr;
using Neutron::Utility::staticCast;
using Neutron::Utility::dynamicCast;
using Neutron::Utility::reinterpretCast;
using Neutron::Utility::MessageBus;

namespace Neutron
{
	namespace System
	{
		// plugins
		class NeutronPlugin;

		// devices
		class Device;
		class SystemDevice;
		class RenderDevice;

		typedef RCPtr<Device>			DevicePtr;
		typedef RCPtr<SystemDevice>		SystemDevicePtr;
		typedef RCPtr<RenderDevice>		RenderDevicePtr;
	}

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

		typedef RCPtr<Resource>			ResourcePtr;
		typedef RCPtr<Image>			ImagePtr;
		typedef RCPtr<InputStream>		InputStreamPtr;
		typedef RCPtr<Buffer>			BufferPtr;
		typedef RCPtr<Texture>			TexturePtr;
		typedef RCPtr<Sampler>			SamplerPtr;
		typedef RCPtr<Shader>			ShaderPtr;
		typedef RCPtr<Viewport>			ViewportPtr;
		typedef RCPtr<Window>			WindowPtr;
	}

	namespace Message
	{
		// message channel
		enum : int
		{
			MC_System,
			MC_Engine
		};

		struct MessagePluginRelease
		{
			System::NeutronPlugin* plugin;
		};
	}
}