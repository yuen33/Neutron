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
				IT_Unknown,
				IT_1D,
				IT_2D,
				IT_3D,
				IT_Cube
			};

		private:
			int		imageType;
			int		width;
			int		height;
			int		depth;
			int64	format;
			int		arraySize;
			int		mips;
			uint8*	data;
			Size	size;

		public:
			static ImagePtr create( Device* owner );

			Image( Device* owner );
			virtual ~Image();

			boolean init1D( int width, uint64 format, int mips, int arraySize );
			boolean init2D( int width, int height, uint64 format, int mips, int arraySize );
			boolean init3D( int width, int height, int depth, uint64 format, int mips );
			boolean initCube( int width, int height, uint64 format, int mips, int numOfCubes );
			void release();

			inline bool null() const { return data != 0; }
			inline int getImageType() const { return imageType; }
			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
			inline int getDepth() const { return depth; }
			inline int64 getFormat() const { return format; }
			inline int getArraySize() const { return arraySize; }
			inline int getMips() const { return mips; }
			inline const uint8* getData() const { return data; }
			inline uint8* getData() { return data; }
			inline Size getSize() const { return size; }
		};
	}
}