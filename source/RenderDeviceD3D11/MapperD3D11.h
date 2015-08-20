#pragma once

#include "RenderDeviceD3D11Common.h"

#include <dxgi.h>
#include <d3d11.h>

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class MapperD3D11
			{
			public:
				MapperD3D11();
				virtual ~MapperD3D11();

				static DXGI_FORMAT mapPixelFormat( uint64 format );
				static uint64 mapPixelFormat( DXGI_FORMAT dxgiFormat );

				static D3D11_FILTER mapFilterType( int filterType );
				static int mapFilterType( D3D11_FILTER d3dFilterType );

				static D3D11_TEXTURE_ADDRESS_MODE mapAddressMode( int addressMode );
				static int mapAddressMode( D3D11_TEXTURE_ADDRESS_MODE d3dAddressMode );

				static D3D11_COMPARISON_FUNC mapComparisonFunction( int comparisonFunction );
				static int mapComparisonFunction( D3D11_COMPARISON_FUNC d3dComparisonFunction );

				static boolean getD3DBufferFlags( int bufferType, int accessHint, Size stride, D3D11_USAGE& usage, UINT& cpuAccessFlag, UINT& bindFlag, UINT& miscFlag );
				static boolean getD3DTextureFlags( int textureType, int accessHint, uint64 format, int mips, D3D11_USAGE& d3dUsage, UINT& bindFlag, UINT& cpuAccessFlag, UINT& miscFlag);
			};
		}
	}
}