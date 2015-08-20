#include "SamplerD3D11.h"
#include "NeutronFoundation/Vector4.h"
#include <d3d11.h>
#include "MapperD3D11.h"
#include "RenderDeviceD3D11.h"

using Neutron::Math::float4;
using Neutron::System::RenderDeviceD3D11;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			SamplerPtr SamplerD3D11::createSampler( Device* owner )
			{
				return SamplerPtr( new SamplerD3D11( owner ) );
			}

			SamplerD3D11::SamplerD3D11( Device* owner )
				: Sampler( owner )
				, d3dSamplerState( 0 )
			{
			}

			SamplerD3D11::~SamplerD3D11()
			{
			}

			boolean SamplerD3D11::init( int filterType, int addressModeU, int addressModeV, int addressModeW, float mipLODBias, int maxAnisotropy, int comparisonFunction, float4 borderColor, float minLOD, float maxLOD )
			{
				if( !owner || filterType <= FT_Unknown || addressModeU <= AM_Unknown || addressModeV <= AM_Unknown || addressModeW <= AM_Unknown || maxAnisotropy < 0 || comparisonFunction <= CF_Unknown )
				{
					return false;
				}

				D3D11_SAMPLER_DESC desc;
				desc.Filter = MapperD3D11::mapFilterType( filterType );
				desc.AddressU = MapperD3D11::mapAddressMode( addressModeU );
				desc.AddressV = MapperD3D11::mapAddressMode( addressModeV );
				desc.AddressW = MapperD3D11::mapAddressMode( addressModeW );
				desc.MipLODBias = mipLODBias;
				desc.MaxAnisotropy = maxAnisotropy;
				desc.ComparisonFunc = MapperD3D11::mapComparisonFunction( comparisonFunction );
				desc.BorderColor[0] = borderColor[0];
				desc.BorderColor[1] = borderColor[1];
				desc.BorderColor[2] = borderColor[2];
				desc.BorderColor[3] = borderColor[3];
				desc.MinLOD = minLOD;
				desc.MaxLOD = maxLOD;

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				HRESULT hr = d3dDevice->CreateSamplerState( &desc, &d3dSamplerState );
				if( SUCCEEDED( hr ) )
				{
					return true;
				}
				return false;
			}

			void SamplerD3D11::release()
			{
				if( d3dSamplerState )
				{
					d3dSamplerState->Release();
					d3dSamplerState = 0;
				}
			}
		}
	}
}