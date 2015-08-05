#include "TextureD3D11.h"
#include "NeutronSystem/PixelFormat.h"
#include "RenderDeviceD3D11.h"
#include "MapperD3D11.h"
#include "NeutronFoundation/Hash.h"
#include "NeutronSystem/Image.h"

using Neutron::System::RenderDeviceD3D11;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			TexturePtr TextureD3D11::createTexture( Device* owner )
			{
				return TexturePtr( new TextureD3D11( owner ) );
			}

			TextureD3D11::TextureD3D11( Engine::Device* owner )
				: Texture( owner )
				, accessHint( RenderDeviceD3D11::AH_Unknown )
				, arraySize( 0 )
				, d3dFormat( DXGI_FORMAT_UNKNOWN )
				, d3dResource( 0 )
			{
			}

			TextureD3D11::~TextureD3D11()
			{
				release();
			}

			boolean TextureD3D11::init1D( int width, uint64 format, int mips, int arraySize, int accessHint, Texture::InitData const* initData )
			{
				// prepare parameters
				if( owner == 0 || width <= 0 || format == PF_Unknown || accessHint == RenderDeviceD3D11::AH_Unknown )
				{
					return false;
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();

				if( mips == 0 )
				{
					mips = getMipsCount( width, 0, 0 );
				}

				if( arraySize == 0 )
				{
					arraySize = 1;
				}

				// generate d3d flags
				D3D11_USAGE usage;
				UINT bindFlag;
				UINT cpuAccessFlag;
				UINT miscFlag;

				if( !MapperD3D11::getD3DTextureFlags( TT_1D, accessHint, format, mips, usage, bindFlag, cpuAccessFlag, miscFlag ) )
				{
					return false;
				}

				// fill desc
				D3D11_TEXTURE1D_DESC desc;
				desc.Width = width;
				desc.Format = MapperD3D11::mapPixelFormat( format );
				desc.MipLevels = mips;
				desc.Usage = usage;
				desc.BindFlags = bindFlag;
				desc.CPUAccessFlags = cpuAccessFlag;
				desc.MiscFlags = miscFlag;

				// fill init data
				Array<D3D11_SUBRESOURCE_DATA> subresData;
				if( initData )
				{
					subresData.reserve( arraySize * mips );
					for( int i = 0; i < arraySize; ++i )
					{
						for( int j = 0; j < mips; ++j )
						{
							int offset = i * mips + j;
							subresData[offset].pSysMem = initData[offset].data;
							subresData[offset].SysMemPitch = initData[offset].rowPitch;
							subresData[offset].SysMemSlicePitch = initData[offset].slicePitch;
						}
					}
				}

				// create resource
				ID3D11Texture1D* d3dTexture = 0;
				HRESULT hr = d3dDevice->CreateTexture1D( &desc, initData ? subresData.getData() : 0, &d3dTexture );
				if( SUCCEEDED( hr ) )
				{
					this->textureType = TT_1D;
					this->d3dResource = d3dTexture;
					d3dTexture->GetDesc( &desc );
					this->d3dFormat = desc.Format;
					this->accessHint = accessHint;
					this->arraySize = arraySize;
					this->sampleCount = 0;
					
					if( accessHint & RenderDeviceD3D11::AH_GenerateMips && mips > 1 )
					{
						getD3DSRV( 0, arraySize, 0, mips );
					}

					return true;
				}

				return false;
			}

			boolean TextureD3D11::init2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData )
			{
				// prepare parameters
				if( owner == 0 || width <= 0 || height <= 0 || format == PF_Unknown || accessHint == RenderDeviceD3D11::AH_Unknown )
				{
					return false;
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();

				if( mips == 0 )
				{
					mips = getMipsCount( width, height, 0 );
				}

				if( arraySize == 0 )
				{
					arraySize = 1;
				}

				if( sampleCount == 0 )
				{
					sampleCount = 1;
				}

				// generate flags
				D3D11_USAGE usage;
				UINT bindFlag;
				UINT cpuAccessFlag;
				UINT miscFlag;
				if( !MapperD3D11::getD3DTextureFlags( TT_2D, accessHint, format, mips, usage, bindFlag, cpuAccessFlag, miscFlag ) )
				{
					return false;
				}

				// fill desc
				D3D11_TEXTURE2D_DESC desc;
				desc.Width = width;
				desc.Height = height;
				desc.Format = MapperD3D11::mapPixelFormat( format );
				desc.MipLevels = mips;
				desc.ArraySize = arraySize;
				desc.SampleDesc.Count = sampleCount;
				desc.SampleDesc.Quality = sampleQuality;
				desc.Usage = usage;
				desc.BindFlags = bindFlag;
				desc.CPUAccessFlags = cpuAccessFlag;
				desc.MiscFlags = miscFlag;

				// fill init data
				Array<D3D11_SUBRESOURCE_DATA> subresData;
				if( initData )
				{
					subresData.resize( arraySize * mips );
					for( int i = 0; i < arraySize; ++i )
					{
						for( int j = 0; j < mips; ++j )
						{
							int offset = i * mips + j;
							subresData[offset].pSysMem = initData[offset].data;
							subresData[offset].SysMemPitch = initData[offset].rowPitch;
							subresData[offset].SysMemSlicePitch = initData[offset].slicePitch;
						}
					}
				}

				// create resource
				ID3D11Texture2D* d3dTexture = 0;
				HRESULT hr = d3dDevice->CreateTexture2D( &desc, initData ? subresData.getData() : 0, &d3dTexture );
				if( SUCCEEDED( hr ) )
				{
					this->textureType = TT_2D;
					this->d3dResource = d3dTexture;
					d3dTexture->GetDesc( &desc );
					this->d3dFormat = desc.Format;
					this->accessHint = accessHint;
					this->arraySize = arraySize;
					this->sampleCount = sampleCount;

					if( accessHint & RenderDeviceD3D11::AH_GenerateMips && mips > 1 )
					{
						getD3DSRV( 0, arraySize, 0, mips );
					}

					return true;
				}

				return false;
			}

			boolean TextureD3D11::init3D( int width, int height, int depth, uint64 format, int mips, int accessHint, Texture::InitData const* initData )
			{
				// prepare parameters
				if( owner == 0 || width <= 0 || height <= 0 || depth <= 0 || format == PF_Unknown || accessHint == RenderDeviceD3D11::AH_Unknown )
				{
					return false;
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();

				if( mips = 0 )
				{
					mips = getMipsCount( width, height, depth );
				}

				// generate flags
				D3D11_USAGE usage;
				UINT bindFlag;
				UINT cpuAccessFlag;
				UINT miscFlag;
				if( !MapperD3D11::getD3DTextureFlags( TT_3D, accessHint, format, mips, usage, bindFlag, cpuAccessFlag, miscFlag ) )
				{
					return false;
				}

				// fill desc
				D3D11_TEXTURE3D_DESC desc;
				desc.Width = width;
				desc.Height = height;
				desc.Depth = depth;
				desc.Format = MapperD3D11::mapPixelFormat( format );
				desc.MipLevels = mips;
				desc.Usage = usage;
				desc.BindFlags = bindFlag;
				desc.CPUAccessFlags = cpuAccessFlag;
				desc.MiscFlags = miscFlag;

				// fill init data
				Array<D3D11_SUBRESOURCE_DATA> subresData;
				if( initData )
				{
					subresData.reserve( mips );
					for( int j = 0; j < mips; ++j )
					{
						subresData[j].pSysMem = initData[j].data;
						subresData[j].SysMemPitch = initData[j].rowPitch;
						subresData[j].SysMemSlicePitch = initData[j].slicePitch;
					}
				}

				// create resource
				ID3D11Texture3D* d3dTexture = 0;
				HRESULT hr = d3dDevice->CreateTexture3D( &desc, initData ? subresData.getData() : 0, &d3dTexture );
				if( SUCCEEDED( hr ) )
				{
					this->textureType = TT_3D;
					this->d3dResource = d3dTexture;
					d3dTexture->GetDesc( &desc );
					this->d3dFormat = desc.Format;
					this->accessHint = accessHint;
					this->arraySize = arraySize;
					this->sampleCount = 0;

					if( mips > 1 && ( accessHint & RenderDeviceD3D11::AH_GenerateMips ) != 0 )
					{
						getD3DSRV( 0, 0, 0, mips );
					}

					return true;
				}

				return false;
			}

			boolean TextureD3D11::initCube( int width, int height, uint64 format, int mips, int numOfCubes, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData )
			{
				// prepare parameters
				if( owner == 0 || width <= 0 || numOfCubes <= 0 || format == PF_Unknown || accessHint == RenderDeviceD3D11::AH_Unknown )
				{
					return false;
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();

				if( sampleCount == 0 )
				{
					sampleCount = 1;
				}

				int arraySize = numOfCubes * 6;

				// generate flags
				D3D11_USAGE usage;
				UINT bindFlag;
				UINT cpuAccessFlag;
				UINT miscFlag;
				if( !MapperD3D11::getD3DTextureFlags( TT_Cube, accessHint, format, mips, usage, bindFlag, cpuAccessFlag, miscFlag ) )
				{
					return false;
				}

				// fill desc
				D3D11_TEXTURE2D_DESC desc;
				desc.Width = width;
				desc.Height = height;
				desc.Format = MapperD3D11::mapPixelFormat( format );
				desc.MipLevels = mips;
				desc.ArraySize = arraySize;
				desc.SampleDesc.Count = sampleCount;
				desc.SampleDesc.Quality = sampleQuality;
				desc.Usage = usage;
				desc.BindFlags = bindFlag;
				desc.CPUAccessFlags = cpuAccessFlag;
				desc.MiscFlags = miscFlag;

				// fill init data
				Array<D3D11_SUBRESOURCE_DATA> subresData;
				if( initData )
				{
					subresData.resize( arraySize * mips );
					for( int i = 0; i < arraySize; ++i )
					{
						for( int j = 0; j < mips; ++j )
						{
							int offset = i * mips + j;
							subresData[offset].pSysMem = initData[offset].data;
							subresData[offset].SysMemPitch = initData[offset].rowPitch;
							subresData[offset].SysMemSlicePitch = initData[offset].slicePitch;
						}
					}
				}

				// create resource
				ID3D11Texture2D* d3dTexture = 0;
				HRESULT hr = d3dDevice->CreateTexture2D( &desc, initData ? subresData.getData() : 0, &d3dTexture );
				if( SUCCEEDED( hr ) )
				{
					this->textureType = TT_Cube;
					this->d3dResource = d3dTexture;
					d3dTexture->GetDesc( &desc );
					this->d3dFormat = desc.Format;
					this->accessHint = accessHint;
					this->arraySize = arraySize;
					this->sampleCount = sampleCount;

					if( accessHint & RenderDeviceD3D11::AH_GenerateMips && mips > 1 )
					{
						getD3DSRV( 0, arraySize, 0, mips );
					}

					return true;
				}

				return false;
			}

			boolean TextureD3D11::initFromImage( ImagePtr image, uint32 sampleCount, uint32 sampleQuality, uint32 accessHint )
			{
				if( owner == 0 || image.isNull() || accessHint == RenderDeviceD3D11::AH_Unknown )
				{
					return false;
				}

				switch( image->getImageType() )
				{
					case Image::IT_1D:
					{
						InitData initData;
						initData.data = image->getData();
						initData.rowPitch = 0;
						initData.slicePitch = 0;
						return init1D( image->getWidth(), image->getFormat(), image->getMips(), image->getArraySize(), accessHint, &initData );
					}
					break;

					case Image::IT_2D:
					{
						InitData initData;
						initData.data = image->getData();
						initData.rowPitch = (int)getPitchSize( image->getFormat(), image->getWidth() );
						initData.slicePitch = initData.rowPitch * image->getHeight();
						return init2D( image->getWidth(), image->getHeight(), image->getFormat(), image->getMips(), image->getArraySize(), sampleCount, sampleQuality, accessHint, &initData );
					}
					break;

					case Image::IT_3D:
					{
						InitData initData;
						initData.data = image->getData();
						initData.rowPitch = (int)getPitchSize( image->getFormat(), image->getWidth() );
						initData.slicePitch = initData.rowPitch * image->getHeight();
						return init3D( image->getWidth(), image->getHeight(), image->getHeight(), image->getFormat(), image->getMips(), accessHint, &initData );
					}
					break;

					case Image::IT_Cube:
					{
						InitData initData;
						initData.data = image->getData();
						initData.rowPitch = (int)getPitchSize( image->getFormat(), image->getWidth() );
						initData.slicePitch = initData.rowPitch * image->getHeight();
						return initCube( image->getWidth(), image->getHeight(), image->getFormat(), image->getMips(), image->getArraySize() / 6, sampleCount, sampleQuality, accessHint, &initData );
					}
					break;

					default:
					{
					}
				}

				return false;
			}

			void TextureD3D11::release()
			{
				// clear all views
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

				for( HashMap<uint32, ID3D11RenderTargetView*>::Iterator it = rtvCache.begin(); it != rtvCache.end(); ++it )
				{
					it.value()->Release();
				}
				rtvCache.clear();

				for( HashMap<uint32, ID3D11DepthStencilView*>::Iterator it = dsvCache.begin(); it != dsvCache.end(); ++it )
				{
					it.value()->Release();
				}
				dsvCache.clear();

				// clear d3d resource
				if( d3dResource )
				{
					d3dResource->Release();
					d3dResource = 0;
				}

				accessHint = RenderDeviceD3D11::AH_Unknown;
				arraySize = 0;
				d3dFormat = DXGI_FORMAT_UNKNOWN;
			}

			boolean TextureD3D11::fillShaderResourceViewDesc( D3D11_SHADER_RESOURCE_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex, int mips )
			{
				memset( &desc, 0, sizeof( desc ) );
				desc.Format = d3dFormat;

				switch( textureType )
				{
					case TT_1D:
					{
						if( arraySize > 1 )
						{
							desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
							desc.Texture1DArray.MostDetailedMip = mipIndex;
							desc.Texture1DArray.MipLevels = mips;
							desc.Texture1DArray.FirstArraySlice = arrayIndex;
							desc.Texture1DArray.ArraySize = numOfItems;
						}
						else
						{
							desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
							desc.Texture1D.MostDetailedMip = mipIndex;
							desc.Texture1D.MipLevels = mips;
						}
					}
					break;

					case TT_2D:
					case TT_Cube:
					{
						if( arraySize > 1 )
						{
							if( sampleCount > 1 )
							{
								desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
							}
							else
							{
								desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
							}

							desc.Texture2DArray.MostDetailedMip = mipIndex;
							desc.Texture2DArray.MipLevels = mips;
							desc.Texture2DArray.FirstArraySlice = arrayIndex;
							desc.Texture2DArray.ArraySize = numOfItems;
						}
						else
						{
							if( sampleCount > 1 )
							{
								desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
							}
							else
							{
								desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
							}

							desc.Texture2D.MostDetailedMip = mipIndex;
							desc.Texture2D.MipLevels = mips;
						}
					}
					break;

					case TT_3D:
					{
						desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
						desc.Texture3D.MostDetailedMip = mipIndex;
						desc.Texture3D.MipLevels = mips;
					}
					break;

					default:
					{
						return false;
					}
				}

				return true;
			}

			boolean TextureD3D11::fillUnorderedAccessViewDesc( D3D11_UNORDERED_ACCESS_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex, int wslices )
			{
				memset( &desc, 0, sizeof( desc ) );
				desc.Format = d3dFormat;
				
				switch( textureType )
				{
					case TT_1D:
					{
						if( arraySize > 1 )
						{
							desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1DARRAY;
							desc.Texture1DArray.MipSlice = mipIndex;
							desc.Texture1DArray.FirstArraySlice = arrayIndex;
							desc.Texture1DArray.ArraySize = numOfItems;
						}
						else
						{
							desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
							desc.Texture1D.MipSlice = mipIndex;							
						}
					}
					break;

					case TT_2D:
					case TT_Cube:
					{
						if( arraySize > 1 )
						{
							desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
							desc.Texture2DArray.MipSlice = mipIndex;
							desc.Texture2DArray.FirstArraySlice = arrayIndex;
							desc.Texture2DArray.ArraySize = numOfItems;
						}
						else
						{
							desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
							desc.Texture2D.MipSlice = mipIndex;
						}
					}
					break;

					case TT_3D:
					{
						desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
						desc.Texture3D.MipSlice = mipIndex;
						desc.Texture3D.FirstWSlice = wsliceIndex;
						desc.Texture3D.WSize = wslices;
					}
					break;

					default:
					{
						return false;
					}
				}

				return true;
			}

			boolean TextureD3D11::fillRenderTargetViewDesc( D3D11_RENDER_TARGET_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex, int wslices )
			{
				memset( &desc, 0, sizeof( desc ) );
				desc.Format = d3dFormat;
				
				switch( textureType )
				{
					case TT_1D:
					{
						if( arraySize > 1 )
						{
							desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
							desc.Texture1DArray.MipSlice = mipIndex;
							desc.Texture1DArray.FirstArraySlice = arrayIndex;
							desc.Texture1DArray.ArraySize = numOfItems;
						}
						else
						{
							desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
							desc.Texture1D.MipSlice = mipIndex;							
						}
					}
					break;

					case TT_2D:
					case TT_Cube:
					{
						if( arraySize > 1 )
						{
							if( sampleCount > 1 )
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
							}
							else
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
							}
							desc.Texture2DArray.MipSlice = mipIndex;
							desc.Texture2DArray.FirstArraySlice = arrayIndex;
							desc.Texture2DArray.ArraySize = numOfItems;
						}
						else
						{
							if( sampleCount > 1 )
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
							}
							else
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
							}
							desc.Texture2D.MipSlice = mipIndex;
						}
					}
					break;

					case TT_3D:
					{
						desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
						desc.Texture3D.MipSlice = mipIndex;
						desc.Texture3D.FirstWSlice = wsliceIndex;
						desc.Texture3D.WSize = wslices;
					}
					break;

					default:
					{
						return false;
					}
				}

				return true;
			}

			boolean TextureD3D11::fillDepthStencilViewDesc( D3D11_DEPTH_STENCIL_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex )
			{
				memset( &desc, 0, sizeof( desc ) );
				desc.Format = d3dFormat;
				
				switch( textureType )
				{
					case TT_1D:
					{
						if( arraySize > 1 )
						{
							desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1DARRAY;
							desc.Texture1DArray.MipSlice = mipIndex;
							desc.Texture1DArray.FirstArraySlice = arrayIndex;
							desc.Texture1DArray.ArraySize = numOfItems;
						}
						else
						{
							desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1D;
							desc.Texture1D.MipSlice = mipIndex;
						}
					}
					break;

					case TT_2D:
					case TT_Cube:
					{
						if( arraySize > 1 )
						{
							if( sampleCount > 1 )
							{
								desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
							}
							else
							{
								desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
							}
							desc.Texture2DArray.MipSlice = mipIndex;
							desc.Texture2DArray.FirstArraySlice = arrayIndex;
							desc.Texture2DArray.ArraySize = numOfItems;
						}
						else
						{
							if( sampleCount > 1 )
							{
								desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
							}
							else
							{
								desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
							}
							desc.Texture2D.MipSlice = mipIndex;
						}
					}
					break;

					case TT_3D:
					{
						return false;
					}
					break;

					default:
					{
						return false;
					}
				}

				return true;
			}

			ID3D11ShaderResourceView* TextureD3D11::getD3DSRV( int arrayIndex, int numOfItems, int mipIndex, int mips )
			{
				if( !owner || d3dResource == 0 || ( accessHint & RenderDeviceD3D11::AH_GPU_Read ) == 0 || arrayIndex + numOfItems >= arraySize )
				{
					return 0;
				}

				D3D11_SHADER_RESOURCE_VIEW_DESC desc;
				if( !fillShaderResourceViewDesc( desc, arrayIndex, numOfItems, mipIndex, mips ) )
				{
					return 0;
				}

				// retrive or create and cache d3d view
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

			ID3D11UnorderedAccessView* TextureD3D11::getD3DUAV( int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex, int wslices )
			{
				if( !owner || d3dResource == 0 || ( accessHint & RenderDeviceD3D11::AH_GPU_Unordered ) == 0 || arrayIndex + numOfItems >= arraySize )
				{
					return 0;
				}

				D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
				if( !fillUnorderedAccessViewDesc( desc, arrayIndex, numOfItems, mipIndex, wsliceIndex, wslices ) )
				{
					return 0;
				}

				// retrive or create and cache d3d view
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

			ID3D11RenderTargetView* TextureD3D11::getD3DRTV( int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex, int wslices )
			{
				if( !owner || d3dResource == 0 || ( accessHint & RenderDeviceD3D11::AH_GPU_Write ) == 0 || arrayIndex + numOfItems >= arraySize )
				{
					return 0;
				}

				D3D11_RENDER_TARGET_VIEW_DESC desc;
				if( !fillRenderTargetViewDesc( desc, arrayIndex, numOfItems, mipIndex, wsliceIndex, wslices ) )
				{
					return 0;
				}
				
				// retrive or create and cache d3d view
				const char* p = reinterpret_cast<const char*>( &desc );
				uint32 hashValue = Math::Hash::DJB32( p, sizeof( desc ) );
				HashMap<uint32, ID3D11RenderTargetView*>::Iterator it = rtvCache.find( hashValue );
				if( it != rtvCache.end() )
				{
					return it.value();
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				ID3D11RenderTargetView* d3dRTV = 0;
				HRESULT hr = d3dDevice->CreateRenderTargetView( d3dResource, &desc, &d3dRTV );
				if( FAILED( hr ) )
				{
					return 0;
				}

				rtvCache.add( hashValue, d3dRTV );
				return d3dRTV;
			}

			ID3D11DepthStencilView* TextureD3D11::getD3DDSV( int arrayIndex, int numOfItems, int mipIndex )
			{
				if( !owner || d3dResource == 0 || ( accessHint & RenderDeviceD3D11::AH_GPU_Write ) == 0 || arrayIndex + numOfItems >= arraySize )
				{
					return 0;
				}

				D3D11_DEPTH_STENCIL_VIEW_DESC desc;
				if( !fillDepthStencilViewDesc( desc, arrayIndex, numOfItems, mipIndex ) )
				{
					return 0;
				}
				
				// retrive or create and cache d3d view
				const char* p = reinterpret_cast<const char*>( &desc );
				uint32 hashValue = Math::Hash::DJB32( p, sizeof( desc ) );
				HashMap<uint32, ID3D11DepthStencilView*>::Iterator it = dsvCache.find( hashValue );
				if( it != dsvCache.end() )
				{
					return it.value();
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				ID3D11DepthStencilView* d3dDSV = 0;
				HRESULT hr = d3dDevice->CreateDepthStencilView( d3dResource, &desc, &d3dDSV );
				if( FAILED( hr ) )
				{
					return 0;
				}

				dsvCache.add( hashValue, d3dDSV );
				return d3dDSV;
			}
		}
	}
}