#include "Image.h"
#include "PixelFormat.h"

namespace Neutron
{
	namespace Engine
	{
		Image::Image( Device* owner )
			: Resource( owner )
		{
			resourceType = RT_Image;
			release();
		}

		Image::~Image()
		{
			release();
		}

		boolean Image::init1D( int width, uint64 format, int mips, int arraySize )
		{
			// regularization parameters
			if( width <= 0 || format == Render::PF_UNKNOWN )
			{
				return false;
			}

			if( mips <= 0 )
			{
				mips = 1;
			}

			if( arraySize <= 0 )
			{
				arraySize = 1;
			}

			size = Render::getImage1DSize( width, format, mips, arraySize );
			if( size > 0 )
			{
				data = new uint8[size];
				assert( data );
				if( data )
				{
					this->type = Image_1D;
					this->width = width;
					this->format = format;
					this->mips = mips;
					this->arraySize = arraySize;
					return true;
				}
			}

			return false;
		}

		boolean Image::init2D( int width, int height, uint64 format, int mips, int arraySize )
		{
			// regularization parameters
			if( width <= 0 || height <= 0 || format == Render::PF_UNKNOWN )
			{
				return false;
			}

			if( mips <= 0 )
			{
				mips = 1;
			}

			if( arraySize <= 0 )
			{
				arraySize = 1;
			}

			size = Render::getImage2DSize( width, height, format, mips, arraySize );
			if( size > 0 )
			{
				data = new uint8[size];
				assert( data );
				if( data )
				{
					this->type = Image_2D;
					this->width = width;
					this->height = height;
					this->format = format;
					this->mips = mips;
					this->arraySize = arraySize;
					return true;
				}
			}

			return false;
		}

		boolean Image::init3D( int width, int height, int depth, uint64 format, int mips )
		{
			// regularization parameters
			if( width <= 0 || height <= 0 || depth <= 0 || format == Render::PF_UNKNOWN )
			{
				return false;
			}

			if( mips <= 0 )
			{
				mips = 1;
			}

			size = Render::getImage3DSize( width, height, depth, format, mips );
			if( size > 0 )
			{
				data = new uint8[size];
				assert( data );
				if( data )
				{
					this->type = Image_3D;
					this->width = width;
					this->height = height;
					this->depth = depth;
					this->format = format;
					this->mips = mips;
					return true;
				}
			}

			return false;
		}

		boolean Image::initCube( int width, int height, uint64 format, int mips, int numOfCubes )
		{
			// regularization parameters
			if( width <= 0 || height <= 0 || numOfCubes <= 0 || format == Render::PF_UNKNOWN )
			{
				return false;
			}

			if( mips <= 0 )
			{
				mips = 1;
			}

			size = Render::getImageCubeSize( width, height, format, mips, numOfCubes );
			if( size > 0 )
			{
				data = new uint8[size];
				assert( data );
				if( data )
				{
					this->type = Image_3D;
					this->width = width;
					this->height = height;
					this->format = format;
					this->mips = mips;
					this->arraySize = numOfCubes * 6;
					return true;
				}
			}

			return false;
		}

		void Image::release()
		{
			type = Image_Unknown;
			width = 0;
			height = 0;
			depth = 0;
			format = Render::PF_UNKNOWN;
			arraySize = 1;
			mips = 1;
			if( data )
			{
				delete[] data;
				data = 0;
			}
			size = 0;
		}

		ImagePtr Image::create()
		{
			return ImagePtr( new Image( 0 ) );
		}

		ImagePtr Image::create1D( int width, uint64 format, int mips, int arraySize )
		{
			ImagePtr image = create();
			if( !image.isNull() && image->init1D( width, format, mips, arraySize ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr Image::create2D( int width, int height, uint64 format, int mips, int arraySize )
		{
			ImagePtr image = create();
			if( !image.isNull() && image->init2D( width, height, format, mips, arraySize ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr Image::create3D( int width, int height, int depth, uint64 format, int mips )
		{
			ImagePtr image = create();
			if( !image.isNull() && image->init3D( width, height, depth, format, mips ) )
			{
				return image;
			}

			return ImagePtr::null;
		}

		ImagePtr Image::createCube( int width, int height, uint64 format, int mips, int numOfCubes )
		{
			ImagePtr image = create();
			if( !image.isNull() && image->initCube( width, height, format, mips, numOfCubes ) )
			{
				return image;
			}

			return ImagePtr::null;
		}
	}
}