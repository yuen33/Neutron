#pragma once

#include "NeutronSystemCommon.h"
#include "EngineDefine.h"

namespace Neutron
{
	namespace Engine
	{
		class ResourceDescriptor
		{
		public:
			ResourceDescriptor();
			virtual ~ResourceDescriptor();
		};

		class Resource : public RCObject
		{
		public:
			Resource() {};
			virtual ~Resource() {};
		};

		template<typename DescriptorType>
		class ResourceConcrete
		{
			DescriptorType			descriptor;

		public:
			ResourceConcrete();
			virtual ~ResourceConcrete();

			virtual DescriptorType& getDiscriptor() const = 0;
			virtual int getTypeID() const = 0;
			virtual Size getSize() const = 0;
		};
	}
}