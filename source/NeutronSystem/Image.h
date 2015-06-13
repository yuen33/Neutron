#pragma once

#include "NeutronSystemCommon.h"
#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		class ImageDescriptor : public ResourceDescriptor
		{
		public:
			ImageDescriptor();
			ImageDescriptor( const ImageDescriptor& other );
			virtual ~ImageDescriptor();

			ImageDescriptor& operator=( const ImageDescriptor& rhs );
			
		};

		class Image : public ResourceConcrete<ImageDescriptor>
		{
		};
	}
}