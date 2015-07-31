#include "FileRenderGraph.h"
#include "NeutronFoundation/FileJson.h"

using Neutron::Utility::FileJson;

namespace Neutron
{
	namespace System
	{
		namespace File
		{
			FileRenderGraph::FileRenderGraph()
			{
			}

			FileRenderGraph::~FileRenderGraph()
			{
			}

			RenderablePtr FileRenderGraph::load( const char* path )
			{
				FileJson::Document jdoc;
				if( FileJson::load( jdoc, path ) )
				{

				}
			}

			void FileRenderGraph::save( const char* path, RenderablePtr renderable )
			{
			}
		}
	}
}