#pragma once

#include "NeutronFoundation/Memory.h"
#include "NeutronSystem/PixelFormat.h"
#include "NeutronSystem/Image.h"
#include "NeutronSystem/FileJPEG.h"
#include "NeutronFoundation/CalculationScalar.h"

using namespace Neutron::Engine::Render;
using Neutron::Engine::Image;
using Neutron::System::File::FileJPEG;

using namespace Neutron;

void gaussBlur( ImagePtr sourceImage, ImagePtr targetImage, int sourceChannel, int targetChannel, float radius )
{
	int rs = (int)Math::ceil( radius * 2.57f );
	int h = sourceImage->getHeight();
	int w = sourceImage->getWidth();
	uint8* sourceData = sourceImage->getData();
	uint8* targetData = targetImage->getData();
	for( int y = 0; y < h; ++y )
	{
		for( int x = 0; x < w; ++x )
		{
			float val = 0;
			float wsum = 0;
			for( int iy = y - rs; iy < y + rs + 1; ++iy )
			{
				for( int ix = x - rs; ix < x + rs + 1; ++ix )
				{
					int xx = Math::min( w - 1, Math::max( 0, ix ) );
					int yy = Math::min( h - 1, Math::max( 0, iy ) );
					int dsq = ( ix - x ) * ( ix - x ) + ( iy - y ) * ( iy - y );
					float wght = Math::exp( -(float)dsq / ( 2.0f * radius * radius ) ) / ( Math::PI * 2.0f * radius * radius );
					val += ( sourceData[( yy * w + xx ) * 3 + sourceChannel] * wght );
					wsum += wght;
				}
			}

			targetData[( y * w + x ) * 3 + targetChannel] = Math::round( val / wsum );
		}
	}
}

void test()
{
	Neutron::Memory::init();
	{
		ImagePtr sourceImage = FileJPEG::load( "cballs.jpg" );
		ImagePtr targetImage = Image::create2D( sourceImage->getWidth(), sourceImage->getHeight(), PF_RGB8UN, 1, 1 );
		gaussBlur( sourceImage, targetImage, 0, 0, 5.0f );
		gaussBlur( sourceImage, targetImage, 1, 1, 5.0f );
		gaussBlur( sourceImage, targetImage, 2, 2, 5.0f );
		FileJPEG::save( targetImage, "test_output.jpg", 1.0f );
	}
	Neutron::Memory::release();
}