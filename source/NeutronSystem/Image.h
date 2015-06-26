#pragma once

#include "NeutronSystemCommon.h"
#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE Image : public Resource
		{
		public:
			enum : int
			{
				Image_1D,
				Image_2D,
				Image_3D,
				Image_Cube
			};

		private:
			int		type;
			int		width;
			int		height;
			int		depth;
			int64	format;
			int		arraySize;
			int		mips;
			uint8*	data;
			Size	size;

		public:
			Image();
			virtual ~Image();

			inline bool null() const { return data != 0; }
			inline int getType() const { return type; }
			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
			inline int getDepth() const { return depth; }
			inline int64 getFormat() const { return format; }
			inline int getArraySize() const { return arraySize; }
			inline int getMips() const { return mips; }
			inline const uint8* getData() { return data; }
			inline Size getSize() const { return size; }
		};
	}
}