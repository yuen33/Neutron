#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Texture : public Resource
			{
			public:
				enum : int
				{
					TT_Unknown,
					TT_1D,
					TT_2D,
					TT_3D,
					TT_Cube
				};

				struct InitData
				{
					void*	data;
					int		rowPitch;
					int		slicePitch;
				};

			protected:
				int textureType;

			public:
				static TexturePtr createTexture( Device* owner );

				Texture( Device* owner );
				virtual ~Texture();

				inline int getTextureType() const { return textureType; }
			};
		}
	}
}