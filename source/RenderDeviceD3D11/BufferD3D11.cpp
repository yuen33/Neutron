#include "BufferD3D11.h"
#include "RenderDeviceD3D11/RenderDeviceD3D11.h"
#include "MapperD3D11.h"
#include "NeutronSystem/PixelFormat.h"
#include "NeutronFoundation/Hash.h"

using Neutron::System::RenderDeviceD3D11;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			BufferD3D11::BufferD3D11( Engine::Device* owner )
				: Buffer( owner )
				, d3dResource( 0 )
			{
			}

			BufferD3D11::~BufferD3D11()
			{
				release();
			}

			boolean BufferD3D11::init( int bufferType, int accessHint, Size stride, Size size )
			{
				if( owner != 0 || bufferType == BT_Unknown || accessHint == RenderDeviceD3D11::AH_Unknown || size == 0 )
				{
					return false;
				}

				// d3d require cbuffe size to be 16 bytes aligned;
				if( bufferType == BT_ConstBuffer )
				{
					size = ( size + 15 ) / 16 * 16;
				}

				D3D11_BUFFER_DESC desc;
				memset( &desc, 0, sizeof( desc ) );
				if( !MapperD3D11::getD3DBufferFlags( bufferType, accessHint, stride, desc.Usage, desc.CPUAccessFlags, desc.BindFlags, desc.MiscFlags ) )
				{
					return false;
				}

				desc.StructureByteStride = (UINT)stride;
				desc.ByteWidth = (UINT)size;

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();

				ID3D11Buffer* d3dBuffer = 0;
				HRESULT hr = d3dDevice->CreateBuffer( &desc, 0, &d3dBuffer );
				if( SUCCEEDED( hr ) )
				{
					this->d3dResource = d3dBuffer;
					this->bufferType = bufferType;
					this->accessHint = accessHint;
					this->stride = stride;
					this->size = desc.ByteWidth;
					return true;
				}

				return false;
			}

			boolean BufferD3D11::init( int bufferType, int accessHint, Size stride, InitData* initData )
			{
				if( owner == 0 || bufferType == BT_Unknown || accessHint == RenderDeviceD3D11::AH_Unknown || initData == 0 )
				{
					return false;
				}

				if( bufferType == BT_ConstBuffer && initData->rowPitch % 16 > 0 )
				{
					return false;
				}

				D3D11_BUFFER_DESC desc;
				memset( &desc, 0, sizeof( desc ) );
				if( !MapperD3D11::getD3DBufferFlags( bufferType, accessHint, stride, desc.Usage, desc.CPUAccessFlags, desc.BindFlags, desc.MiscFlags ) )
				{
					return false;
				}

				desc.StructureByteStride = 0;
				desc.ByteWidth = initData->rowPitch;

				D3D11_SUBRESOURCE_DATA subresInit;
				subresInit.pSysMem = initData->data;
				subresInit.SysMemPitch = initData->rowPitch;
				subresInit.SysMemSlicePitch = initData->slicePitch;

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				
				ID3D11Buffer* d3dBuffer = 0;
				HRESULT hr = d3dDevice->CreateBuffer( &desc, &subresInit, &d3dBuffer );
				if( SUCCEEDED( hr ) )
				{
					this->d3dResource = d3dBuffer;
					this->bufferType = bufferType;
					this->accessHint = accessHint;
					this->stride = stride;
					this->size = desc.ByteWidth;
					return true;
				}

				return false;
			}

			void BufferD3D11::release()
			{
				for( HashMap<uint32, ID3D11ShaderResourceView*>::Iterator it = srvCache.begin(); it != srvCache.end(); ++it )
				{
					it.value()->Release();
				}
				srvCache.clear();

				for( HashMap<uint32, ID3D11UnorderedAccessView*>::Iterator it = uavCache.begin(); it != uavCache.end(); ++it )
				{
					it.value()->Release();
				}
				uavCache.clear();

				if( d3dResource )
				{
					d3dResource->Release();
				}
			}

			void* BufferD3D11::map( int mapType )
			{
				D3D11_MAP d3dMapType;
				if( mapType == MT_ReadOnly && ( accessHint & RenderDeviceD3D11::AH_CPU_Read ) )
				{
					d3dMapType = D3D11_MAP_READ;
				}
				else if( mapType == MT_WriteOnly && ( accessHint & RenderDeviceD3D11::AH_CPU_Write ) )
				{
					d3dMapType = D3D11_MAP_WRITE_DISCARD;
				}
				else if( mapType == MT_ReadWrite && ( accessHint & RenderDeviceD3D11::AH_CPU_Read ) && ( accessHint & RenderDeviceD3D11::AH_CPU_Write ) )
				{
					d3dMapType = D3D11_MAP_READ_WRITE;
				}
				else
				{
					return 0;
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11DeviceContext* d3dContext = rd->getD3DContext();

				D3D11_MAPPED_SUBRESOURCE subres;
				d3dContext->Map( d3dResource, 0, d3dMapType, 0, &subres );

				return subres.pData;
			}

			void BufferD3D11::unmap()
			{
				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11DeviceContext* d3dContext = rd->getD3DContext();

				d3dContext->Unmap( d3dResource, 0 );
			}

			void BufferD3D11::updateResource( const void* p )
			{
				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11DeviceContext* d3dContext = rd->getD3DContext();

				d3dContext->UpdateSubresource( d3dResource, 0, 0, p, 0, 0 );
			}

			ID3D11ShaderResourceView* BufferD3D11::getD3DSRV( uint64 format )
			{
				D3D11_SHADER_RESOURCE_VIEW_DESC desc;
				memset( &desc, 0, sizeof( desc ) );
				desc.Format = MapperD3D11::mapPixelFormat( format );
				desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
				desc.Buffer.FirstElement = 0;
				desc.Buffer.NumElements = (UINT)( stride > 0 ? size / stride : size / getFormatSize( format ) );

				const char* p = reinterpret_cast<const char*>( &desc );
				uint32 hashValue = Math::Hash::DJB32( p, sizeof( desc ) );

				HashMap<uint32, ID3D11ShaderResourceView*>::Iterator it = srvCache.find( hashValue );
				if( it != srvCache.end() )
				{
					return it.value();
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				ID3D11ShaderResourceView* d3dSRV = 0;
				HRESULT hr = d3dDevice->CreateShaderResourceView( d3dResource, &desc, &d3dSRV );
				if( FAILED( hr ) )
				{
					return 0;
				}

				srvCache.add( hashValue, d3dSRV );
				return d3dSRV;
			}

			ID3D11UnorderedAccessView* BufferD3D11::getD3DUAV( uint64 format )
			{
				D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
				memset( &desc, 0, sizeof( desc ) );
				desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
				if( accessHint & RenderDeviceD3D11::AH_Raw )
				{
					desc.Format = DXGI_FORMAT_R32_TYPELESS;
					desc.Buffer.NumElements = (UINT)( size / 4U );
				}
				else if( stride > 0 )
				{
					desc.Format = DXGI_FORMAT_UNKNOWN;
					desc.Buffer.NumElements = (UINT)( size / stride );
				}
				else
				{
					desc.Format = MapperD3D11::mapPixelFormat( format );
					desc.Buffer.NumElements = (UINT)( size / getFormatSize( format ) );
				}

				desc.Buffer.FirstElement = 0;
				desc.Buffer.Flags = 0;
				if( accessHint & RenderDeviceD3D11::AH_Raw )
				{
					desc.Buffer.Flags |= D3D11_BUFFER_UAV_FLAG_RAW;
				}
				if( accessHint & RenderDeviceD3D11::AH_Append )
				{
					desc.Buffer.Flags |= D3D11_BUFFER_UAV_FLAG_APPEND;
				}
				if( accessHint & RenderDeviceD3D11::AH_Counter )
				{
					desc.Buffer.Flags |= D3D11_BUFFER_UAV_FLAG_COUNTER;
				}

				const char* p = reinterpret_cast<const char*>( &desc );
				uint32 hashValue = Math::Hash::DJB32( p, sizeof( desc ) );

				HashMap<uint32, ID3D11UnorderedAccessView*>::Iterator it = uavCache.find( hashValue );
				if( it != uavCache.end() )
				{
					return it.value();
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				ID3D11UnorderedAccessView* d3dUAV = 0;
				HRESULT hr = d3dDevice->CreateUnorderedAccessView( d3dResource, &desc, &d3dUAV );
				if( FAILED( hr ) )
				{
					return 0;
				}

				uavCache.add( hashValue, d3dUAV );
				return d3dUAV;
			}
		}
	}
}