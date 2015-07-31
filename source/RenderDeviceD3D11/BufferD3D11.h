#include "NeutronSystem/Buffer.h"
#include "NeutronFoundation/HashMap.h"

#include <d3d11.h>

using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class BufferD3D11 : public Buffer
			{
				ID3D11Resource*								d3dResource;
				int											accessHint;
				Size										stride;
				Size										size;

				HashMap<uint32, ID3D11ShaderResourceView*>	srvCache;
				HashMap<uint32, ID3D11UnorderedAccessView*> uavCache;

			public:
				BufferD3D11( Engine::Device* owner );
				virtual ~BufferD3D11();

				boolean init( int bufferType, int accessHint, Size stride, Size size );
				boolean init( int bufferType, int accessHint, Size stride, InitData* initData );
				void release();

				virtual void* map( int mapType );
				virtual void unmap();
				virtual void updateResource( const void* p );

				ID3D11ShaderResourceView* getD3DSRV( uint64 format );
				ID3D11UnorderedAccessView* getD3DUAV( uint64 format );
			};
		}
	}
}