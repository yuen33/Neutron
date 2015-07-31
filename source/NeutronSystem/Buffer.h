#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Buffer : public Resource
			{
			protected:
				int bufferType;

			public:
				// buffer type
				enum : int
				{
					BT_Unknown,
					BT_IndexBuffer,
					BT_VertexBuffer,
					BT_ConstBuffer,
					BT_ShaderResource
				};

				// map type
				enum : int
				{
					MT_ReadOnly,
					MT_WriteOnly,
					MT_ReadWrite
				};

				struct InitData
				{
					void*	data;
					int		rowPitch;
					int		slicePitch;
				};

			public:
				Buffer( Device* owner );
				virtual ~Buffer();

				virtual void* map( int mapType ) = 0;
				virtual void unmap() = 0;
				virtual void updateResource( const void* p ) = 0;

				inline int getBufferType() const { return bufferType; }
			};
		}
	}
}