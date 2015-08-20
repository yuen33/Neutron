#pragma once

#include "Resource.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Sampler : public Resource
			{
			public:
				// filter type
				enum : int
				{
					FT_Unknown,
					FT_PPP,
					FT_PLP,
					FT_PLL,
					FT_LPL,
					FT_LLP,
					FT_LLL,
					FT_Anisotropic,
					FT_Comparison_PPP,
					FT_Comparison_PPL,
					FT_Comparison_PLP,
					FT_Comparison_PLL,
					FT_Comparison_LPL,
					FT_Comparison_LLP,
					FT_Comparison_LLL,
					FT_Comparison_Anisotropic
				};

				// address mode
				enum : int
				{
					AM_Unknown,
					AM_Wrap,
					AM_Mirror,
					AM_Clamp,
					AM_Border,
					AM_MirrorOnce
				};

				// comparison function
				enum : int
				{
					CF_Unknown,
					CF_Never,
					CF_Less,
					CF_Equal,
					CF_LessEqual,
					CF_Greater,
					CF_NotEqual,
					CF_GreaterEqual,
					CF_Always
				};

			public:
				Sampler( Device* owner );
				virtual ~Sampler();
			};
		}
	}
}