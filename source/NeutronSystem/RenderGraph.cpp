#include "RenderGraph.h"
#include "NeutronFoundation/CompileHash.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			// RenderNode
			RenderNode::RenderNode()
			{
			}

			RenderNode::~RenderNode()
			{
			}

			// RenderInputStreamNode
			RenderNodePtr RenderInputStreamNode::createRenderInputStreamNode()
			{
				return RenderNodePtr::null;
			}

			RenderNodePtr RenderInputStreamNode::createRenderInputStreamNode( const FileJson::Value& jvalue )
			{
				return RenderNodePtr::null;
			}

			RenderInputStreamNode::RenderInputStreamNode()
			{
			}

			RenderInputStreamNode::~RenderInputStreamNode()
			{
			}

			// RenderBufferNode
			RenderNodePtr RenderBufferNode::createRenderBufferNode()
			{
				return RenderNodePtr( new RenderBufferNode() );
			}

			RenderNodePtr RenderBufferNode::createRenderBufferNode( const FileJson::Value& jvalue )
			{
				return RenderNodePtr::null;
			}

			RenderBufferNode::RenderBufferNode()
			{
			}

			RenderBufferNode::~RenderBufferNode()
			{
			}

			// RenderTextureNode
			RenderNodePtr RenderTextureNode::createRenderTextureNode()
			{
				return RenderNodePtr::null;
			}

			RenderNodePtr RenderTextureNode::createRenderTextureNode( const FileJson::Value& jvalue, int textureType )
			{
				return RenderNodePtr::null;
			}

			RenderTextureNode::RenderTextureNode()
			{
			}

			RenderTextureNode::~RenderTextureNode()
			{
			}
			
			// RenderSamplerNode
			RenderNodePtr RenderSamplerNode::createRenderSamplerNode()
			{
				return RenderNodePtr::null;
			}

			RenderNodePtr RenderSamplerNode::createRenderSamplerNode( const FileJson::Value& jvalue )
			{
				return RenderNodePtr::null;
			}

			RenderSamplerNode::RenderSamplerNode()
			{
			}

			RenderSamplerNode::~RenderSamplerNode()
			{
			}

			// RenderShaderNode
			RenderNodePtr RenderShaderNode::createRenderShaderNode()
			{
				return RenderNodePtr::null;
			}

			RenderNodePtr RenderShaderNode::createRenderShaderNode( const FileJson::Value& jvalue, int shaderType )
			{
				return RenderNodePtr::null;
			}

			RenderShaderNode::RenderShaderNode()
			{
			}

			RenderShaderNode::~RenderShaderNode()
			{
			}

			// RenderPipelineNode
			RenderNodePtr RenderPipelineNode::createRenderPipelineNode()
			{
				return RenderNodePtr( new RenderPipelineNode );
			}

			RenderNodePtr RenderPipelineNode::createRenderPipelineNode( const FileJson::Value& jvalue )
			{
				RenderNodePtr pp = createRenderPipelineNode();
				RenderPipelineNode* ppNode = static_cast<RenderPipelineNode*>( pp.get() );
				JSON_FOREACH_CONST_IN_OBJECT( itMember, jvalue )
				{
					uint32 hashValue = Math::Hash::DJB32( itMember->name.GetString() );
					if( STRING_STUB( parameter ) == hashValue )
					{
						ParameterPtr p = Parameter::createParameter( itMember->value );
						if( !p.isNull() )
						{
							ppNode->addParameter( p );
						}
					}
					else if( STRING_STUB( inputStream ) == hashValue )
					{
						RenderNodePtr p = RenderInputStreamNode::createRenderInputStreamNode( itMember->value );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( cbuffer ) == hashValue )
					{
						RenderNodePtr p = RenderBufferNode::createRenderBufferNode( itMember->value );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( texture1D ) == hashValue )
					{
						RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_1D );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( texture2D ) == hashValue )
					{
						RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_2D );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( texture3D ) == hashValue )
					{
						RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_3D );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( textureCube ) == hashValue )
					{
						RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_Cube );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( sampler ) == hashValue )
					{
						RenderNodePtr p = RenderSamplerNode::createRenderSamplerNode( itMember->value );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( shaderVS ) == hashValue )
					{
						RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_VertexShader );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( shaderHS ) == hashValue )
					{
						RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_HullShader );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( shaderDS ) == hashValue )
					{
						RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_DomainShader );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( shaderGS ) == hashValue )
					{
						RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_GeometryShader );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( shaderPS ) == hashValue )
					{
						RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_PixelShader );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( shaderCS ) == hashValue )
					{
						RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_ComputeShader );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else if( STRING_STUB( pipeline ) == hashValue )
					{
						RenderNodePtr p = RenderPipelineNode::createRenderPipelineNode( itMember->value );
						if( !p.isNull() )
						{
							ppNode->addChild( p );
						}
					}
					else
					{
						// invalid node type
						assert( 0 );
					}
				}
				return RenderNodePtr::null;
			}

			RenderPipelineNode::RenderPipelineNode()
			{
			}

			RenderPipelineNode::~RenderPipelineNode()
			{
			}
		}
	}
}