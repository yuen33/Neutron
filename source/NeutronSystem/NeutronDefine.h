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

		typedef RCPtr<Device>				DevicePtr;
		typedef RCPtr<SystemDevice>			SystemDevicePtr;
		typedef RCPtr<RenderDevice>			RenderDevicePtr;
	}

	namespace Engine
	{
		// common
		class Variable;
		class Parameter;
		typedef RCPtr<Variable>				VariablePtr;
		typedef RCPtr<Parameter>			ParameterPtr;

		// pipeline
		class Pin;
		class ProcessingUnit;
		class ProcessingModule;
		class DataFrame;
		class DataStream;
		typedef RCPtr<Pin>					PinPtr;
		typedef RCPtr<ProcessingUnit>		ProcessingUnitPtr;
		typedef RCPtr<ProcessingModule>		ProcessingModulePtr;
		typedef RCPtr<DataFrame>			DataFramePtr;
		typedef RCPtr<DataStream>			DataStreamPtr;

		// resources
		class Resource;
		class Image;
		class Viewport;
		class Window;
		typedef RCPtr<Resource>				ResourcePtr;
		typedef RCPtr<Image>				ImagePtr;
		typedef RCPtr<Viewport>				ViewportPtr;
		typedef RCPtr<Window>				WindowPtr;

		namespace Render
		{
			// resource
			class InputStream;
			class Buffer;
			class Texture;
			class Sampler;
			class Shader;
			class RenderNode;
			class Renderable;

			typedef RCPtr<InputStream>		InputStreamPtr;
			typedef RCPtr<Buffer>			BufferPtr;
			typedef RCPtr<Texture>			TexturePtr;
			typedef RCPtr<Sampler>			SamplerPtr;
			typedef RCPtr<Shader>			ShaderPtr;
			typedef RCPtr<RenderNode>		RenderNodePtr;
			typedef RCPtr<Renderable>		RenderablePtr;

			// module
			class Renderer;
			typedef RCPtr<Renderer>			RendererPtr;
		}
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