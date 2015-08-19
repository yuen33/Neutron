#pragma once

#include "NeutronSystemCommon.h"
#include "Renderable.h"

using Neutron::Engine::Render::RenderNodePtr;
using Neutron::Engine::ParameterPtr;

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

				static RenderNodePtr load( const char* path );
				static void save( const char* path, RenderNodePtr renderNode );
			};
		}
	}
}