#include "MapperD3D11.h"
#include "NeutronSystem/PixelFormat.h"
#include "RenderDeviceD3D11/RenderDeviceD3D11.h"

using Neutron::System::RenderDeviceD3D11;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			MapperD3D11::MapperD3D11()
			{
			}

			MapperD3D11::~MapperD3D11()
			{
			}

			DXGI_FORMAT MapperD3D11::mapPixelFormat( uint64 format )
			{
				switch( format )
				{
					// R8
					case PF_R8UN:				return DXGI_FORMAT_R8_UNORM;
					case PF_R8SN:				return DXGI_FORMAT_R8_SNORM;
					case PF_R8U:				return DXGI_FORMAT_R8_UINT;
					case PF_R8S:				return DXGI_FORMAT_R8_SINT;
						// A8
					case PF_A8UN:				return DXGI_FORMAT_A8_UNORM;
						// RG8
					case PF_RG8UN:				return DXGI_FORMAT_R8G8_UNORM;
					case PF_RG8SN:				return DXGI_FORMAT_R8G8_SNORM;
					case PF_RG8U:				return DXGI_FORMAT_R8G8_UINT;
					case PF_RG8S:				return DXGI_FORMAT_R8G8_SINT;
						// RGBA8
					case PF_RGBA8UN:			return DXGI_FORMAT_R8G8B8A8_UNORM;
					case PF_RGBA8SN:			return DXGI_FORMAT_R8G8B8A8_SNORM;
					case PF_RGBA8U:				return DXGI_FORMAT_R8G8B8A8_UINT;
					case PF_RGBA8S:				return DXGI_FORMAT_R8G8B8A8_SINT;
					case PF_RGBA8SRGB:			return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
						// R16
					case PF_R16UN:				return DXGI_FORMAT_R16_UNORM;
					case PF_R16SN:				return DXGI_FORMAT_R16_SNORM;
					case PF_R16U:				return DXGI_FORMAT_R16_UINT;
					case PF_R16S:				return DXGI_FORMAT_R16_SINT;
					case PF_R16F:				return DXGI_FORMAT_R16_FLOAT;
						// RG16
					case PF_RG16UN:				return DXGI_FORMAT_R16G16_UNORM;
					case PF_RG16SN:				return DXGI_FORMAT_R16G16_SNORM;
					case PF_RG16U:				return DXGI_FORMAT_R16G16_UINT;
					case PF_RG16S:				return DXGI_FORMAT_R16G16_SINT;
					case PF_RG16F:				return DXGI_FORMAT_R16G16_FLOAT;
						// RGBA16
					case PF_RGBA16UN:			return DXGI_FORMAT_R16G16B16A16_UNORM;
					case PF_RGBA16SN:			return DXGI_FORMAT_R16G16B16A16_SNORM;
					case PF_RGBA16U:			return DXGI_FORMAT_R16G16B16A16_UINT;
					case PF_RGBA16S:			return DXGI_FORMAT_R16G16B16A16_SINT;
					case PF_RGBA16F:			return DXGI_FORMAT_R16G16B16A16_FLOAT;
						// R32
					case PF_R32U:				return DXGI_FORMAT_R32_UINT;
					case PF_R32S:				return DXGI_FORMAT_R32_SINT;
					case PF_R32F:				return DXGI_FORMAT_R32_FLOAT;
						// RG32
					case PF_RG32U:				return DXGI_FORMAT_R32G32_UINT;
					case PF_RG32S:				return DXGI_FORMAT_R32G32_SINT;
					case PF_RG32F:				return DXGI_FORMAT_R32G32_FLOAT;
						// RGB32
					case PF_RGB32U:				return DXGI_FORMAT_R32G32B32_UINT;
					case PF_RGB32S:				return DXGI_FORMAT_R32G32B32_SINT;
					case PF_RGB32F:				return DXGI_FORMAT_R32G32B32_FLOAT;
						// RGBA32
					case PF_RGBA32U:			return DXGI_FORMAT_R32G32B32A32_UINT;
					case PF_RGBA32S:			return DXGI_FORMAT_R32G32B32A32_SINT;
					case PF_RGBA32F:			return DXGI_FORMAT_R32G32B32A32_FLOAT;
						// B5G6R5
					case PF_B5G6R5UN:			return DXGI_FORMAT_B5G6R5_UNORM;
						// BGR5A1
					case PF_BGR5A1UN:			return DXGI_FORMAT_B5G5R5A1_UNORM;
						// BGRA8
					case PF_BGRA8UN:			return DXGI_FORMAT_B8G8R8A8_UNORM;
					case PF_BGRA8SRGB:			return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
						// RGB10A2
					case PF_RGB10A2UN:			return DXGI_FORMAT_R10G10B10A2_UNORM;
					case PF_RGB10A2U:			return DXGI_FORMAT_R10G10B10A2_UINT;
						// RG11B10F
					case PF_RG11B10F:			return DXGI_FORMAT_R11G11B10_FLOAT;
						// RGBG8
					case PF_RGBG8UN:			return DXGI_FORMAT_R8G8_B8G8_UNORM;
						// GRGB8
					case PF_GRGB8UN:			return DXGI_FORMAT_G8R8_G8B8_UNORM;
						// BC1
					case PF_BC1UN:				return DXGI_FORMAT_BC1_UNORM;
					case PF_BC1SRGB:			return DXGI_FORMAT_BC1_UNORM_SRGB;
						// BC2
					case PF_BC2UN:				return DXGI_FORMAT_BC2_UNORM;
					case PF_BC2SRGB:			return DXGI_FORMAT_BC2_UNORM_SRGB;
						// BC3
					case PF_BC3UN:				return DXGI_FORMAT_BC3_UNORM;
					case PF_BC3SRGB:			return DXGI_FORMAT_BC3_UNORM_SRGB;
						// BC4
					case PF_BC4UN:				return DXGI_FORMAT_BC4_UNORM;
					case PF_BC4SN:				return DXGI_FORMAT_BC4_SNORM;
						// BC5
					case PF_BC5UN:				return DXGI_FORMAT_BC5_UNORM;
					case PF_BC5SN:				return DXGI_FORMAT_BC5_SNORM;
						// BC6
					case PF_BC6UN:				return DXGI_FORMAT_BC6H_UF16;
					case PF_BC6SN:				return DXGI_FORMAT_BC6H_SF16;
						// BC7
					case PF_BC7UN:				return DXGI_FORMAT_BC7_UNORM;
					case PF_BC7SRGB:			return DXGI_FORMAT_BC7_UNORM_SRGB;
						// D16
					case PF_D16:				return DXGI_FORMAT_D16_UNORM;
						// D24S8
					case PF_D24S8:				return DXGI_FORMAT_D24_UNORM_S8_UINT;
						// D32F
					case PF_D32F:				return DXGI_FORMAT_D32_FLOAT;

					default:
					{
					}
				};

				assert( 0 );
				return DXGI_FORMAT_UNKNOWN;
			}

			uint64 MapperD3D11::mapPixelFormat( DXGI_FORMAT format )
			{
				switch( format )
				{
					case DXGI_FORMAT_R8_UNORM:				return PF_R8UN;
					case DXGI_FORMAT_R8_SNORM:				return PF_R8UN;
					case DXGI_FORMAT_R8_UINT:				return PF_R8U;
					case DXGI_FORMAT_R8_SINT:				return PF_R8S;
					case DXGI_FORMAT_A8_UNORM:				return PF_A8UN;
					case DXGI_FORMAT_R8G8_UNORM:			return PF_RG8UN;
					case DXGI_FORMAT_R8G8_SNORM:			return PF_RG8SN;
					case DXGI_FORMAT_R8G8_UINT:				return PF_RG8U;
					case DXGI_FORMAT_R8G8_SINT:				return PF_RG8S;
					case DXGI_FORMAT_R8G8B8A8_UNORM:		return PF_RGBA8UN;
					case DXGI_FORMAT_R8G8B8A8_SNORM:		return PF_RGBA8SN;
					case DXGI_FORMAT_R8G8B8A8_UINT:			return PF_RGBA8U;
					case DXGI_FORMAT_R8G8B8A8_SINT:			return PF_RGBA8S;
					case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:	return PF_RGBA8SRGB;
					case DXGI_FORMAT_R16_UNORM:				return PF_R16UN;
					case DXGI_FORMAT_R16_SNORM:				return PF_R16SN;
					case DXGI_FORMAT_R16_UINT:				return PF_R16U;
					case DXGI_FORMAT_R16_SINT:				return PF_R16S;
					case DXGI_FORMAT_R16_FLOAT:				return PF_R16F;
					case DXGI_FORMAT_R16G16_UNORM:			return PF_RG16UN;
					case DXGI_FORMAT_R16G16_SNORM:			return PF_RG16SN;
					case DXGI_FORMAT_R16G16_UINT:			return PF_RG16U;
					case DXGI_FORMAT_R16G16_SINT:			return PF_RG16S;
					case DXGI_FORMAT_R16G16_FLOAT:			return PF_RG16F;
					case DXGI_FORMAT_R16G16B16A16_UNORM:	return PF_RGBA16UN;
					case DXGI_FORMAT_R16G16B16A16_SNORM:	return PF_RGBA16SN;
					case DXGI_FORMAT_R16G16B16A16_UINT:		return PF_RGBA16U;
					case DXGI_FORMAT_R16G16B16A16_SINT:		return PF_RGBA16S;
					case DXGI_FORMAT_R16G16B16A16_FLOAT:	return PF_RGBA16F;
					case DXGI_FORMAT_R32_UINT:				return PF_R32U;
					case DXGI_FORMAT_R32_SINT:				return PF_R32S;
					case DXGI_FORMAT_R32_FLOAT:				return PF_R32F;
					case DXGI_FORMAT_R32G32_UINT:			return PF_RG32U;
					case DXGI_FORMAT_R32G32_SINT:			return PF_RG32S;
					case DXGI_FORMAT_R32G32_FLOAT:			return PF_RG32F;
					case DXGI_FORMAT_R32G32B32_UINT:		return PF_RGB32U;
					case DXGI_FORMAT_R32G32B32_SINT:		return PF_RGB32S;
					case DXGI_FORMAT_R32G32B32_FLOAT:		return PF_RGB32F;
					case DXGI_FORMAT_R32G32B32A32_UINT:		return PF_RGBA32U;
					case DXGI_FORMAT_R32G32B32A32_SINT:		return PF_RGBA32S;
					case DXGI_FORMAT_R32G32B32A32_FLOAT:	return PF_RGBA32F;
					case DXGI_FORMAT_B5G6R5_UNORM:			return PF_B5G6R5UN;
					case DXGI_FORMAT_B5G5R5A1_UNORM:		return PF_BGR5A1UN;
					case DXGI_FORMAT_B8G8R8A8_UNORM:		return PF_BGRA8UN;
					case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:	return PF_BGRA8SRGB;
					case DXGI_FORMAT_R10G10B10A2_UNORM:		return PF_RGB10A2UN;
					case DXGI_FORMAT_R10G10B10A2_UINT:		return PF_RGB10A2U;
					case DXGI_FORMAT_R11G11B10_FLOAT:		return PF_RG11B10F;
					case DXGI_FORMAT_R8G8_B8G8_UNORM:		return PF_RGBG8UN;
					case DXGI_FORMAT_G8R8_G8B8_UNORM:		return PF_GRGB8UN;
					case DXGI_FORMAT_BC1_UNORM:				return PF_BC1UN;
					case DXGI_FORMAT_BC1_UNORM_SRGB:		return PF_BC1SRGB;
					case DXGI_FORMAT_BC2_UNORM:				return PF_BC2UN;
					case DXGI_FORMAT_BC2_UNORM_SRGB:		return PF_BC2SRGB;
					case DXGI_FORMAT_BC3_UNORM:				return PF_BC3UN;
					case DXGI_FORMAT_BC3_UNORM_SRGB:		return PF_BC3SRGB;
					case DXGI_FORMAT_BC4_UNORM:				return PF_BC4UN;
					case DXGI_FORMAT_BC4_SNORM:				return PF_BC4SN;
					case DXGI_FORMAT_BC5_UNORM:				return PF_BC5UN;
					case DXGI_FORMAT_BC5_SNORM:				return PF_BC5SN;
					case DXGI_FORMAT_BC6H_UF16:				return PF_BC6UN;
					case DXGI_FORMAT_BC6H_SF16:				return PF_BC6SN;
					case DXGI_FORMAT_BC7_UNORM:				return PF_BC7UN;
					case DXGI_FORMAT_BC7_UNORM_SRGB:		return PF_BC7SRGB;
					case DXGI_FORMAT_D16_UNORM:				return PF_D16;
					case DXGI_FORMAT_D24_UNORM_S8_UINT:		return PF_D24S8;
					case DXGI_FORMAT_D32_FLOAT:				return PF_D32F;
					default:
					{
					}
				};

				assert( 0 );
				return PF_Unknown;
			}

			boolean MapperD3D11::getD3DBufferFlags( int bufferType, int accessHint, Size stride, D3D11_USAGE& usage, UINT& cpuAccessFlag, UINT& bindFlag, UINT& miscFlag )
			{
				if( accessHint & RenderDeviceD3D11::AH_Immutable )
				{
					usage = D3D11_USAGE_IMMUTABLE;
				}
				else
				{
					if( accessHint & RenderDeviceD3D11::AH_CPU_Write )
					{
						usage = D3D11_USAGE_DYNAMIC;
					}
					else if( accessHint & RenderDeviceD3D11::AH_CPU_Read )
					{
						usage = D3D11_USAGE_STAGING;
					}
					else
					{
						usage = D3D11_USAGE_DEFAULT;
					}
				}

				cpuAccessFlag = 0;
				if( accessHint & RenderDeviceD3D11::AH_CPU_Read )
				{
					cpuAccessFlag |= D3D11_CPU_ACCESS_READ;
				}
				else if( accessHint & RenderDeviceD3D11::AH_CPU_Write )
				{
					cpuAccessFlag |= D3D11_CPU_ACCESS_WRITE;
				}

				bindFlag = 0;
				if( bufferType == Buffer::BT_ConstBuffer )
				{
					bindFlag |= D3D11_BIND_CONSTANT_BUFFER;
				}
				else
				{
					if( bufferType == Buffer::BT_VertexBuffer )
					{
						bindFlag = D3D11_BIND_VERTEX_BUFFER;
					}
					else if( bufferType == Buffer::BT_IndexBuffer )
					{
						bindFlag = D3D11_BIND_INDEX_BUFFER;
					}

					if( bufferType == Buffer::BT_ShaderResource )
					{
						bindFlag |= D3D11_BIND_SHADER_RESOURCE;
					}

					if( accessHint & RenderDeviceD3D11::AH_GPU_Unordered )
					{
						bindFlag |= D3D11_BIND_UNORDERED_ACCESS;
					}
				}

				miscFlag = 0;
				if( bufferType != Buffer::BT_IndexBuffer && stride > 0 )
				{
					miscFlag |= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
				}

				if( accessHint & RenderDeviceD3D11::AH_Raw )
				{
					miscFlag |= D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
				}

				if( accessHint & RenderDeviceD3D11::AH_DrawInDirectArgs )
				{
					miscFlag |= D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
				}

				return true;
			}

			boolean MapperD3D11::getD3DTextureFlags( int textureType, int accessHint, uint64 format, int mips, D3D11_USAGE& d3dUsage, UINT& bindFlag, UINT& cpuAccessFlag, UINT& miscFlag )
			{
				// usage
				if( accessHint & RenderDeviceD3D11::AH_Immutable )
				{
					d3dUsage = D3D11_USAGE_IMMUTABLE;
				}
				else
				{
					if( accessHint & RenderDeviceD3D11::AH_CPU_Read )
					{
						d3dUsage = D3D11_USAGE_STAGING;
					}
					else if( accessHint & RenderDeviceD3D11::AH_CPU_Write )
					{
						d3dUsage = D3D11_USAGE_DYNAMIC;
					}
					else
					{
						d3dUsage = D3D11_USAGE_DEFAULT;
					}
				}

				// bind flag
				bindFlag = 0;
				if( accessHint & RenderDeviceD3D11::AH_GPU_Read || d3dUsage == D3D11_USAGE_DYNAMIC )
				{
					bindFlag |= D3D11_BIND_SHADER_RESOURCE;
				}

				if( accessHint & RenderDeviceD3D11::AH_GPU_Write )
				{
					if( isDepthFormat( format ) && d3dUsage != D3D11_USAGE_STAGING )
					{
						bindFlag |= D3D11_BIND_DEPTH_STENCIL;
					}
					else if( mips == 1 || d3dUsage != D3D11_USAGE_STAGING )
					{
						bindFlag |= D3D11_BIND_RENDER_TARGET;
					}
					else
					{
						return false;
					}
				}

				if( accessHint & RenderDeviceD3D11::AH_GPU_Unordered )
				{
					bindFlag |= D3D11_BIND_UNORDERED_ACCESS;
				}

				// cpu access flag
				cpuAccessFlag = 0;
				if( accessHint & RenderDeviceD3D11::AH_CPU_Read )
				{
					cpuAccessFlag |= D3D11_CPU_ACCESS_READ;
				}
				if( accessHint & RenderDeviceD3D11::AH_CPU_Write )
				{
					cpuAccessFlag |= D3D11_CPU_ACCESS_WRITE;
				}

				// misc flag
				miscFlag = 0;
				if( accessHint & RenderDeviceD3D11::AH_GenerateMips )
				{
					miscFlag |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
				}

				if( textureType == Texture::TT_Cube )
				{
					miscFlag |= D3D11_RESOURCE_MISC_TEXTURECUBE;
				}

				return true;
			}
		}
	}
}