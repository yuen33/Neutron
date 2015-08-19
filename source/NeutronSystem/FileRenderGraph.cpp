#include "FileRenderGraph.h"
#include "NeutronFoundation/FileJson.h"
#include "RenderGraph.h"
#include "RenderGraph.h"
#include "Log.h"

using Neutron::Utility::FileJson;
using Neutron::Engine::Render::RenderPipelineNode;

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

			RenderNodePtr FileRenderGraph::load( const char* path )
			{
				RenderNodePtr ret = RenderNodePtr::null;
				FileJson::Document jdoc;
				if( FileJson::load( jdoc, path ) )
				{
					FileJson::MemberIterator itMember = jdoc.FindMember( "pipeline" );
					if( itMember != jdoc.MemberEnd() )
					{
						ret = RenderPipelineNode::createRenderPipelineNode( itMember->value );
					}
				}
				else
				{
					Log::error( "RenderNode", "create from file %s failed: %s\n", path, FileJson::getErrorMessage( jdoc ) );
				}

				return ret;
			}

			void FileRenderGraph::save( const char* path, RenderNodePtr rendernode )
			{
			}
		}
	}
}