#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/CalculationScalar.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			// pixel channel
			enum
			{
				PC_R = 0UL,
				PC_G = 1UL,
				PC_B = 2UL,
				PC_A = 3UL,
				PC_D = 4UL,
				PC_S = 5UL,
				PC_BC = 6UL,
				PC_E = 7UL
			};

			// pixel channel type
			enum
			{
				PCT_UNORM = 0UL,
				PCT_SNORM = 1UL,
				PCT_UINT = 2UL,
				PCT_SINT = 3UL,
				PCT_FLOAT = 4UL,
				PCT_UNORM_SRGB = 5UL,
				PCT_TYPELESS = 6UL,
				PCT_SHAREDEXP = 7UL
			};

			// pixel format 64 bits
			// 00000000 T3[4] T2[4] T1[4] T0[4] S3[6] S2[6] S1[6] S0[6] C3[4] C2[4] C1[4] C0[4]
			template<uint64 ch0, uint64 ch1, uint64 ch2, uint64 ch3,
				uint64 size0, uint64 size1, uint64 size2, uint64 size3,
				uint64 type0, uint64 type1, uint64 type2, uint64 type3>
			struct MakePixelFormat4
			{
				static uint64 const value = ( ch0 << 0 ) | ( ch1 << 4 ) | ( ch2 << 8 ) | ( ch3 << 12 )
					| ( size0 << 16 ) | ( size1 << 22 ) | ( size2 << 28 ) | ( size3 << 34 )
					| ( type0 << 40 ) | ( type1 << 44 ) | ( type2 << 48 ) | ( type3 << 52 );
			};

			template<uint64 ch0, uint64 ch1, uint64 ch2,
				uint64 size0, uint64 size1, uint64 size2,
				uint64 type0, uint64 type1, uint64 type2>
			struct MakePixelFormat3
			{
				static uint64 const value = MakePixelFormat4<ch0, ch1, ch2, 0, size0, size1, size2, 0, type0, type1, type2, 0>::value;
			};

			template<uint64 ch0, uint64 ch1,
				uint64 size0, uint64 size1,
				uint64 type0, uint64 type1>
			struct MakePixelFormat2
			{
				static uint64 const value = MakePixelFormat3<ch0, ch1, 0, size0, size1, 0, type0, type1, 0>::value;
			};

			template<uint64 ch0,
				uint64 size0,
				uint64 type0>
			struct MakePixelFormat1
			{
				static uint64 const value = MakePixelFormat2<ch0, 0, size0, 0, type0, 0>::value;
			};

			// pixel format
			enum : uint64
			{
				// unknown
				PF_UNKNOWN = 0,

				// alpha format
				// A8
				PF_A8UN = MakePixelFormat1<PC_A, 8, PCT_UNORM>::value,

				// regular format
				// R8
				PF_R8UN = MakePixelFormat1<PC_R, 8, PCT_UNORM>::value,
				PF_R8SN = MakePixelFormat1<PC_R, 8, PCT_SNORM>::value,
				PF_R8U = MakePixelFormat1<PC_R, 8, PCT_UINT>::value,
				PF_R8S = MakePixelFormat1<PC_R, 8, PCT_SINT>::value,
				PF_R8F = MakePixelFormat1<PC_R, 8, PCT_FLOAT>::value,

				// RG8
				PF_RG8UN = MakePixelFormat2<PC_R, PC_G, 8, 8, PCT_UNORM, PCT_UNORM>::value,
				PF_RG8SN = MakePixelFormat2<PC_R, PC_G, 8, 8, PCT_SNORM, PCT_SNORM>::value,
				PF_RG8U = MakePixelFormat2<PC_R, PC_G, 8, 8, PCT_UINT, PCT_UINT>::value,
				PF_RG8S = MakePixelFormat2<PC_R, PC_G, 8, 8, PCT_SINT, PCT_SINT>::value,
				PF_RG8F = MakePixelFormat2<PC_R, PC_G, 8, 8, PCT_FLOAT, PCT_FLOAT>::value,

				// RGB8
				PF_RGB8UN = MakePixelFormat3<PC_R, PC_G, PC_B, 8, 8, 8, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_RGB8SN = MakePixelFormat3<PC_R, PC_G, PC_B, 8, 8, 8, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,
				PF_RGB8U = MakePixelFormat3<PC_R, PC_G, PC_B, 8, 8, 8, PCT_UINT, PCT_UINT, PCT_UINT>::value,
				PF_RGB8S = MakePixelFormat3<PC_R, PC_G, PC_B, 8, 8, 8, PCT_SINT, PCT_SINT, PCT_SINT>::value,
				PF_RGB8F = MakePixelFormat3<PC_R, PC_G, PC_B, 8, 8, 8, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT>::value,

				// RGBA8
				PF_RGBA8UN = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 8, 8, 8, 8, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_RGBA8SN = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 8, 8, 8, 8, PCT_SNORM, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,
				PF_RGBA8U = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 8, 8, 8, 8, PCT_UINT, PCT_UINT, PCT_UINT, PCT_UINT>::value,
				PF_RGBA8S = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 8, 8, 8, 8, PCT_SINT, PCT_SINT, PCT_SINT, PCT_SINT>::value,
				PF_RGBA8F = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 8, 8, 8, 8, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT>::value,

				// R16
				PF_R16UN = MakePixelFormat1<PC_R, 16, PCT_UNORM>::value,
				PF_R16SN = MakePixelFormat1<PC_R, 16, PCT_SNORM>::value,
				PF_R16U = MakePixelFormat1<PC_R, 16, PCT_UNORM>::value,
				PF_R16S = MakePixelFormat1<PC_R, 16, PCT_SINT>::value,
				PF_R16F = MakePixelFormat1<PC_R, 16, PCT_FLOAT>::value,

				// RG16
				PF_RG16UN = MakePixelFormat2<PC_R, PC_G, 16, 16, PCT_UNORM, PCT_UNORM>::value,
				PF_RG16SN = MakePixelFormat2<PC_R, PC_G, 16, 16, PCT_SNORM, PCT_SNORM>::value,
				PF_RG16U = MakePixelFormat2<PC_R, PC_G, 16, 16, PCT_UINT, PCT_UINT>::value,
				PF_RG16S = MakePixelFormat2<PC_R, PC_G, 16, 16, PCT_SINT, PCT_SINT>::value,\
				PF_RG16F = MakePixelFormat2<PC_R, PC_G, 16, 16, PCT_FLOAT, PCT_FLOAT>::value,

				// RGB16
				PF_RGB16UN = MakePixelFormat3<PC_R, PC_G, PC_B, 16, 16, 16, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_RGB16SN = MakePixelFormat3<PC_R, PC_G, PC_B, 16, 16, 16, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,
				PF_RGB16U = MakePixelFormat3<PC_R, PC_G, PC_B, 16, 16, 16, PCT_UINT, PCT_UINT, PCT_UINT>::value,
				PF_RGB16S = MakePixelFormat3<PC_R, PC_G, PC_B, 16, 16, 16, PCT_SINT, PCT_SINT, PCT_SINT>::value,
				PF_RGB16F = MakePixelFormat3<PC_R, PC_G, PC_B, 16, 16, 16, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT>::value,

				// RGBA16
				PF_RGBA16UN = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 16, 16, 16, 16, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_RGBA16SN = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 16, 16, 16, 16, PCT_SNORM, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,
				PF_RGBA16U = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 16, 16, 16, 16, PCT_UINT, PCT_UINT, PCT_UINT, PCT_UINT>::value,
				PF_RGBA16S = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 16, 16, 16, 16, PCT_SINT, PCT_SINT, PCT_SINT, PCT_SINT>::value,
				PF_RGBA16F = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 16, 16, 16, 16, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT>::value,

				// R32
				PF_R32UN = MakePixelFormat1<PC_R, 32, PCT_UNORM>::value,
				PF_R32SN = MakePixelFormat1<PC_R, 32, PCT_SNORM>::value,
				PF_R32U = MakePixelFormat1<PC_R, 32, PCT_UINT>::value,
				PF_R32S = MakePixelFormat1<PC_R, 32, PCT_SINT>::value,
				PF_R32F = MakePixelFormat1<PC_R, 32, PCT_FLOAT>::value,

				// RG32
				PF_RG32UN = MakePixelFormat2<PC_R, PC_G, 32, 32, PCT_UNORM, PCT_UNORM>::value,
				PF_RG32SN = MakePixelFormat2<PC_R, PC_G, 32, 32, PCT_SNORM, PCT_SNORM>::value,
				PF_RG32U = MakePixelFormat2<PC_R, PC_G, 32, 32, PCT_UINT, PCT_UINT>::value,
				PF_RG32S = MakePixelFormat2<PC_R, PC_G, 32, 32, PCT_SINT, PCT_SINT>::value,
				PF_RG32F = MakePixelFormat2<PC_R, PC_G, 32, 32, PCT_FLOAT, PCT_FLOAT>::value,

				// RGB32
				PF_RGB32UN = MakePixelFormat3<PC_R, PC_G, PC_B, 32, 32, 32, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_RGB32SN = MakePixelFormat3<PC_R, PC_G, PC_B, 32, 32, 32, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,
				PF_RGB32U = MakePixelFormat3<PC_R, PC_G, PC_B, 32, 32, 32, PCT_UINT, PCT_UINT, PCT_UINT>::value,
				PF_RGB32S = MakePixelFormat3<PC_R, PC_G, PC_B, 32, 32, 32, PCT_SINT, PCT_SINT, PCT_SINT>::value,
				PF_RGB32F = MakePixelFormat3<PC_R, PC_G, PC_B, 32, 32, 32, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT>::value,

				// RGBA32
				PF_RGBA32UN = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 32, 32, 32, 32, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_RGBA32SN = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 32, 32, 32, 32, PCT_SNORM, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,
				PF_RGBA32U = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 32, 32, 32, 32, PCT_UINT, PCT_UINT, PCT_UINT, PCT_UINT>::value,
				PF_RGBA32S = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 32, 32, 32, 32, PCT_SINT, PCT_SINT, PCT_SINT, PCT_SINT>::value,
				PF_RGBA32F = MakePixelFormat4<PC_R, PC_G, PC_B, PC_A, 32, 32, 32, 32, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT>::value,

				// special format
				// B5G6R5
				PF_B5G6R5UN = MakePixelFormat3<PC_B, PC_G, PC_R, 5, 6, 5, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,

				// BGR5A1
				PF_BGR5A1UN = MakePixelFormat4<PC_B, PC_G, PC_R, PC_A, 5, 5, 5, 1, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,

				// BGRA8
				PF_BGRA8UN = MakePixelFormat4<PC_B, PC_G, PC_R, PC_A, 8, 8, 8, 8, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_BGRA8SN = MakePixelFormat4<PC_B, PC_G, PC_R, PC_A, 8, 8, 8, 8, PCT_SNORM, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,

				// RGB10A2
				PF_BGR10A2UN = MakePixelFormat4<PC_B, PC_G, PC_R, PC_A, 10, 10, 10, 2, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,
				PF_BGR10A2SN = MakePixelFormat4<PC_B, PC_G, PC_R, PC_A, 10, 10, 10, 2, PCT_SNORM, PCT_SNORM, PCT_SNORM, PCT_SNORM>::value,

				// RG11B10F
				PF_RG11B10F = MakePixelFormat3<PC_R, PC_G, PC_B, 11, 11, 10, PCT_FLOAT, PCT_FLOAT, PCT_FLOAT>::value,

				// RGBG8
				PF_RGBG8UN = MakePixelFormat4<PC_R, PC_G, PC_B, PC_G, 8, 8, 8, 8, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,

				// GRGB8
				PF_GRGB8UN = MakePixelFormat4<PC_G, PC_R, PC_G, PC_B, 8, 8, 8, 8, PCT_UNORM, PCT_UNORM, PCT_UNORM, PCT_UNORM>::value,

				// compress format
				// BC1
				PF_BC1UN = MakePixelFormat1<PC_BC, 1, PCT_UNORM>::value,
				PF_BC1UNSRGB = MakePixelFormat1<PC_BC, 1, PCT_UNORM_SRGB>::value,

				// BC2
				PF_BC2UN = MakePixelFormat1<PC_BC, 2, PCT_UNORM>::value,
				PF_BC2UNSRGB = MakePixelFormat1<PC_BC, 2, PCT_UNORM_SRGB>::value,
				
				// BC3
				PF_BC3UN = MakePixelFormat1<PC_BC, 3, PCT_UNORM>::value,
				PF_BC3UNSRGB = MakePixelFormat1<PC_BC, 3, PCT_UNORM_SRGB>::value,

				// BC4
				PF_BC4UN = MakePixelFormat1<PC_BC, 4, PCT_UNORM>::value,
				PF_BC4SN = MakePixelFormat1<PC_BC, 4, PCT_SNORM>::value,

				// BC5
				PF_BC5UN = MakePixelFormat1<PC_BC, 5, PCT_UNORM>::value,
				PF_BC5SN = MakePixelFormat1<PC_BC, 5, PCT_SNORM>::value,

				// BC6
				PF_BC6UN = MakePixelFormat1<PC_BC, 6, PCT_UNORM>::value,
				PF_BC6SN = MakePixelFormat1<PC_BC, 6, PCT_SNORM>::value,

				// BC7
				PF_BC7UN = MakePixelFormat1<PC_BC, 7, PCT_UNORM>::value,
				PF_BC7UNSRGB = MakePixelFormat1<PC_BC, 7, PCT_UNORM_SRGB>::value,

				// depth stencil format
				// D16
				PF_D16 = MakePixelFormat1<PC_D, 16, PCT_UNORM>::value,

				// D24S8
				PF_D24S8 = MakePixelFormat2<PC_D, PC_S, 24, 8, PCT_UNORM, PCT_UINT>::value,

				// D32F
				PF_D32F = MakePixelFormat1<PC_D, 32, PCT_FLOAT>::value,
			};

			template<uint8 c>
			inline uint64 getChannel( uint64 format )
			{
				return static_cast<uint64>( format >> ( 4 * c ) & 0xf );
			}

			template<uint8 c>
			inline uint64 getChannelBitsCount( uint64 format )
			{
				return static_cast<uint64>( format >> ( 16 + 6 * c ) & 0xf );
			}

			template<uint8 c>
			inline uint64 getChannelType( uint64 format )
			{
				return static_cast<uint64>( format >> ( 40 + 4 * c ) & 0xf );
			}

			inline uint32 getChannelCount( uint64 format )
			{
				return (
					( getChannelBitsCount<0>( format ) > 0 ? 1 : 0 ) +
					( getChannelBitsCount<1>( format ) > 0 ? 1 : 0 ) +
					( getChannelBitsCount<2>( format ) > 0 ? 1 : 0 ) +
					( getChannelBitsCount<3>( format ) > 0 ? 1 : 0 ) );
			}

			inline boolean isDepthFormat( uint64 format )
			{
				return getChannelType<0>( format ) == PC_D;
			}

			inline boolean isStencilFormat( uint64 format )
			{
				return getChannelType<1>( format ) == PC_S;
			}

			inline boolean isCompressFormat( uint64 format )
			{
				return getChannelType<0>( format ) == PC_BC;
			}

			static Size getFormatBitsCount( uint64 format )
			{
				if( isCompressFormat( format ) )
				{
					switch( getChannelBitsCount<0>( format ) )
					{
						case 1:
						case 4:
							return 16;
						case 2:
						case 3:
						case 5:
							return 32;

						default:
							{
								// unsupport format
								assert( 0 );
								return 0;
							}
					}
				}

				return static_cast<Size>(
					getChannelBitsCount<0>( format )
					+ getChannelBitsCount<1>( format )
					+ getChannelBitsCount<2>( format )
					+ getChannelBitsCount<3>( format )
				);
			}

			static Size getFormatSize( uint64 format )
			{
				return getFormatBitsCount( format ) / 8;
			}

			static Size getPitchSize( uint64 format, int width )
			{
				// see http://msdn.microsoft.com/en-us/library/bb943991.aspx
				if( isCompressFormat( format ) )
				{
					Size blockSize = 0;
					if( getChannelBitsCount<0>( format ) == 1 || getChannelBitsCount<0>( format ) == 4 )
					{
						blockSize = 8;
					}
					else
					{
						blockSize = 16;
					}

					return width > 0 ? ( ( width + 3 ) / 4 ) * blockSize : 0;
				}
				else if( format == PF_RGBG8UN || format == PF_GRGB8UN )
				{
					return ( ( width + 1 ) >> 1 ) * 4;
				}
				
				return ( width * getFormatBitsCount( format ) + 7 ) / 8;
			}

			static Size getMipsCount( int width, int height, int depth )
			{
				int m = 1;
				while( width || height || depth )
				{
					width <<= 1;
					height <<= 1;
					depth <<= 1;
					++m;
				}

				return m;
			}

			static Size getImage1DSize( uint64 format, int width, int mips, int arraySize )
			{
				if( arraySize == 0 )
				{
					arraySize = 1;
				}

				if( mips == 0 )
				{
					mips = getMipsCount( width, 0, 0 );
				}

				Size sizePerMipSeries = 0;
				for( int i = 0; i < mips; ++i )
				{
					int mipWidth = Math::max( width >> i, 1 );
					sizePerMipSeries += getPitchSize( format, mipWidth );
				}

				return sizePerMipSeries * arraySize;
			}

			static Size getImage2DSize( uint64 format, int width, int height, int mips, int arraySize )
			{
				if( arraySize == 0 )
				{
					arraySize = 1;
				}

				if( mips == 0 )
				{
					mips = getMipsCount( width, height, 0 );
				}

				Size sizePerMipSeries = 0;
				for( int i = 0; i < mips; ++i )
				{
					int mipWidth = Math::max( width >> i, 1 );
					int mipHeight = Math::max( height >> 1, 1 );
					sizePerMipSeries += getPitchSize( format, mipWidth ) * mipHeight;
				}

				return sizePerMipSeries * arraySize;
			}

			static Size getImage3DSize( uint64 format, int width, int height, int depth, int mips )
			{
				if( mips == 0 )
				{
					mips = getMipsCount( width, height, depth );
				}

				Size sizePerMipSeries = 0;
				for( int i = 0; i < mips; ++i )
				{
					int mipWidth = Math::max( width >> i, 1 );
					int mipHeight = Math::max( height >> i, 1 );
					int mipDepth = Math::max( depth >> i, 1 );
					sizePerMipSeries += getPitchSize( format, mipWidth ) * mipHeight * mipDepth;
				}

				return sizePerMipSeries;
			}

			static Size getImageCubeSize( uint64 format, int width, int height, int mips, int cubeCount )
			{
				return getImage2DSize( format, width, height, mips, cubeCount * 6 );
			}
		}
	}
}