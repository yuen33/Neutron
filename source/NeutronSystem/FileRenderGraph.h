#pragma once

#include "NeutronSystemCommon.h"

using Neutron::Engine::Render::RenderablePtr;

namespace Neutron
{
	namespace System
	{
		namespace File
		{
			class NEUTRON_CORE FileRenderGraph
			{
			public:
				FileRenderGraph();
				virtual ~FileRenderGraph();

				static RenderablePtr load( const char* path );
				static void save( const char* path, RenderablePtr renderable );
			};
		}
	}
}