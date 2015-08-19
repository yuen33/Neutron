#include "RenderGraph.h"
#include "NeutronFoundation/CompileHash.h"
#include "RenderSymbol.h"

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
				return RenderNodePtr( new RenderInputStreamNode() );
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
				RenderNodePtr bufferNode = createRenderBufferNode();
				if( !bufferNode.isNull() )
				{
					RenderBufferNode* bufferNodePtr = static_cast<RenderBufferNode*>( bufferNode.get() );
					JSON_FOREACH_CONST_IN_OBJECT( itMember, jvalue )
					{
						uint32 hashValue = Math::Hash::DJB32( itMember->name.GetString() );
						if( hashValue == STRING_STUB( RNK, name ) )
						{
							bufferNodePtr->setName( FileJson::read( itMember->value, String::null ).getCStr() );
						}
						else if( hashValue == STRING_STUB( RNK, semantic ) )
						{
							bufferNodePtr->setSemantic( FileJson::read( itMember->value, String::null ).getCStr() );
						}
						else if( hashValue == STRING_STUB( RNK, accessHint ) )
						{
							bufferNodePtr->accessHint = ParseAccessHint( itMember->value.GetString() );
						}
						else if( hashValue == STRING_STUB( RNK, parameter ) )
						{
							ParameterPtr newParameter = Parameter::createParameter( itMember->value );
							if( !newParameter.isNull() )
							{
								bufferNodePtr->addParameter( newParameter );
							}
						}
					}

					return bufferNode;
				}

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
				return RenderNodePtr( new RenderTextureNode() );
			}

			RenderNodePtr RenderTextureNode::createRenderTextureNode( const FileJson::Value& jvalue, int textureType )
			{
				RenderNodePtr textureNode = createRenderTextureNode();
				if( !textureNode.isNull() )
				{
					RenderTextureNode* textureNodePtr = static_cast<RenderTextureNode*>( textureNode.get() );
					JSON_FOREACH_CONST_IN_OBJECT( itMember, jvalue )
					{
						uint32 hashValue = Math::Hash::DJB32( itMember->name.GetString() );
						if( hashValue == STRING_STUB( RNK, name ) )
						{
							textureNodePtr->setName( FileJson::read( itMember->value, String::null ).getCStr() );
						}
						else if( hashValue == STRING_STUB( RNK, semantic ) )
						{
							textureNodePtr->setSemantic( FileJson::read( itMember->value, String::null ).getCStr() );
						}
						else if( hashValue == STRING_STUB( RGK, width ) )
						{
							textureNodePtr->width = FileJson::read( itMember->value, 0 );
						}
						else if( hashValue == STRING_STUB( RGK, height ) )
						{
							textureNodePtr->height = FileJson::read( itMember->value, 0 );
						}
						else if( hashValue == STRING_STUB( RGK, depth ) )
						{
							textureNodePtr->depth = FileJson::read( itMember->value, 0 );
						}
						else if( hashValue == STRING_STUB( RGK, format ) )
						{
							textureNodePtr->format = FileJson::read( itMember->value, PF_Unknown );
						}
						else if( hashValue == STRING_STUB( RGK, mips ) )
						{
							textureNodePtr->mips = FileJson::read( itMember->value, 1 );
						}
						else if( hashValue == STRING_STUB( RGK, arraySize ) )
						{
							textureNodePtr->arraySize = FileJson::read( itMember->value, 1 );
						}
						else if( hashValue == STRING_STUB( RGK, sampleCount ) )
						{
							textureNodePtr->sampleCount = FileJson::read( itMember->value, 1 );
						}
						else if( hashValue == STRING_STUB( RGK, sampleQuality ) )
						{
							textureNodePtr->sampleQuality = FileJson::read( itMember->value, 0 );
						}
						else if( hashValue == STRING_STUB( RGK, accessHint ) )
						{
							textureNodePtr->accessHint = ParseAccessHint( FileJson::read( itMember->value, String::null ).getCStr() );
						}
					}

					return textureNode;
				}

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
				return RenderNodePtr( new RenderSamplerNode() );
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
				return RenderNodePtr( new RenderShaderNode() );
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
				if( !pp.isNull() )
				{
					RenderPipelineNode* ppNode = static_cast<RenderPipelineNode*>( pp.get() );
					JSON_FOREACH_CONST_IN_OBJECT( itMember, jvalue )
					{
						uint32 hashValue = Math::Hash::DJB32( itMember->name.GetString() );
						if( hashValue == STRING_STUB( RNK, name ) )
						{
							ppNode->setName( FileJson::read( itMember->value, String::null ).getCStr() );
						}
						else if( hashValue == STRING_STUB( RNK, semantic ) )
						{
							ppNode->setSemantic( FileJson::read( itMember->value, String::null ).getCStr() );
						}
						else if( hashValue == STRING_STUB( RGK, parameter ) )
						{
							ParameterPtr p = Parameter::createParameter( itMember->value );
							if( !p.isNull() )
							{
								ppNode->addParameter( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, inputStream ) )
						{
							RenderNodePtr p = RenderInputStreamNode::createRenderInputStreamNode( itMember->value );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, cbuffer ) )
						{
							RenderNodePtr p = RenderBufferNode::createRenderBufferNode( itMember->value );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, texture1D ) )
						{
							RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_1D );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, texture2D ) )
						{
							RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_2D );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, texture3D ) )
						{
							RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_3D );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, textureCube ) )
						{
							RenderNodePtr p = RenderTextureNode::createRenderTextureNode( itMember->value, Texture::TT_Cube );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, sampler ) )
						{
							RenderNodePtr p = RenderSamplerNode::createRenderSamplerNode( itMember->value );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, shaderVS ) )
						{
							RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_VertexShader );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, shaderHS ) )
						{
							RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_HullShader );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, shaderDS ) )
						{
							RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_DomainShader );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, shaderGS ) )
						{
							RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_GeometryShader );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, shaderPS ) )
						{
							RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_PixelShader );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, shaderCS ) )
						{
							RenderNodePtr p = RenderShaderNode::createRenderShaderNode( itMember->value, Shader::ST_ComputeShader );
							if( !p.isNull() )
							{
								ppNode->addChild( p );
							}
						}
						else if( hashValue == STRING_STUB( RGN, pipeline ) )
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

					return pp;
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