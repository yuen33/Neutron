#pragma once

#include "NeutronSystemCommon.h"

namespace Neutron
{
	namespace Engine
	{
		enum : int
		{
			RT_Unknown,
			RT_Image,
			RT_InputStream,
			RT_Buffer,
			RT_Texture,
			RT_Sampler,
			RT_Shader,
			RT_Viewport,
			RT_Renderable
		};
		
		using Neutron::System::Device;

		class NEUTRON_CORE Resource : public RCObject
		{
		protected:
			int resourceType;
			Device* owner;

			virtual void deleteMethod( RCObject* object );

		public:
			Resource( Device* device );
			virtual ~Resource();

			virtual void release() = 0;

			inline int getResourceType() const { return resourceType; }
		};
	}
}