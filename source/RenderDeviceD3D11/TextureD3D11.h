#include "NeutronSystem/Texture.h"
#include "NeutronFoundation/HashMap.h"
#include <dxgi.h>
#include <d3d11.h>

using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class TextureD3D11 : public Texture
			{
				int												accessHint;
				int												arraySize;
				int												sampleCount;

				DXGI_FORMAT										d3dFormat;
				ID3D11Resource*									d3dResource;

				HashMap<uint32, ID3D11ShaderResourceView*>		srvCache;
				HashMap<uint32, ID3D11UnorderedAccessView*>		uavCache;
				HashMap<uint32, ID3D11RenderTargetView*>		rtvCache;
				HashMap<uint32, ID3D11DepthStencilView*>		dsvCache;

				boolean fillShaderResourceViewDesc( D3D11_SHADER_RESOURCE_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex, int mips );
				boolean fillUnorderedAccessViewDesc( D3D11_UNORDERED_ACCESS_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex, int wslices );
				boolean fillRenderTargetViewDesc( D3D11_RENDER_TARGET_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex, int wslices );
				boolean fillDepthStencilViewDesc( D3D11_DEPTH_STENCIL_VIEW_DESC& desc, int arrayIndex, int numOfItems, int mipIndex );

			public:
				static TexturePtr createTexture( Device* owner );
				TextureD3D11( Device* owner );
				virtual ~TextureD3D11();

				boolean init1D( int width, uint64 format, int mips, int arraySize, int accessHint, Texture::InitData const* initData );
				boolean init2D( int width, int height, uint64 format, int mips, int arraySize, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData );
				boolean init3D( int width, int height, int depth, uint64 format, int mips, int accessHint, Texture::InitData const* initData );
				boolean initCube( int width, int height, uint64 format, int mips, int numCubes, int sampleCount, int sampleQuality, int accessHint, Texture::InitData const* initData );
				boolean initFromImage( ImagePtr image, uint32 sampleCount, uint32 sampleQuality, uint32 accessHint );
				void release();

				ID3D11ShaderResourceView* getD3DSRV( int arrayIndex, int numOfItems, int mipIndex, int mips );
				ID3D11UnorderedAccessView* getD3DUAV( int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex = 0, int wslices = 0 );
				ID3D11RenderTargetView* getD3DRTV( int arrayIndex, int numOfItems, int mipIndex, int wsliceIndex = 0, int wslices = 0 );
				ID3D11DepthStencilView* getD3DDSV( int arrayIndex, int numOfItems, int mipIndex );
			};
		}
	}
}