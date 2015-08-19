#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/FileJson.h"
#include "Parameter.h"
#include "NeutronFoundation/CompileHash.h"

using Neutron::Utility::FileJson;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			CREATE_STRING_STUB( parameter );
			CREATE_STRING_STUB( inputStream );
			CREATE_STRING_STUB( cbuffer );
			CREATE_STRING_STUB( texture1D );
			CREATE_STRING_STUB( texture2D );
			CREATE_STRING_STUB( texture3D );
			CREATE_STRING_STUB( textureCube );
			CREATE_STRING_STUB( sampler );
			CREATE_STRING_STUB( shaderVS );
			CREATE_STRING_STUB( shaderHS );
			CREATE_STRING_STUB( shaderDS );
			CREATE_STRING_STUB( shaderGS );
			CREATE_STRING_STUB( shaderPS );
			CREATE_STRING_STUB( shaderCS );
			CREATE_STRING_STUB( pipeline );

			class NEUTRON_CORE RenderNode : public RCObject
			{
			public:
				// node type
				enum : int
				{
					RNT_InputStream,
					RNT_Buffer,
					RNT_Texture,
					RNT_Sampler,
					RNT_Shader,
					RNT_Pipeline
				};

			private:
				int						nodeType;
				String					name;
				String					semantic;

			public:
				RenderNode();
				virtual ~RenderNode();

				inline void setName( const char* str ) { name = str; }
				inline const char* getName() const { return name.getCStr(); }
				inline void setSemantic( const char* str ) { semantic = str; }
				inline const char* getSemantic() const { return semantic.getCStr(); }
				inline int getNodeType() const { return nodeType; }
			};

			class NEUTRON_CORE RenderInputStreamNode : public RenderNode
			{
			public:
				static RenderNodePtr createRenderInputStreamNode();
				static RenderNodePtr createRenderInputStreamNode( const FileJson::Value& jvalue );
				RenderInputStreamNode();
				virtual ~RenderInputStreamNode();
			};

			class NEUTRON_CORE RenderBufferNode : public RenderNode
			{
				int bufferType;
				int accessHint;
				Array<ParameterPtr>		parameters;

			public:
				static RenderNodePtr createRenderBufferNode();
				static RenderNodePtr createRenderBufferNode( const FileJson::Value& jvalue );
				RenderBufferNode();
				virtual ~RenderBufferNode();

				void addParameter( ParameterPtr parameter ) { parameters.add( parameter ); }
				void removeParameter( int index ) { if( index < parameters.getCount() ) { parameters.removeAtFast( index ); } }
				inline int getParameterCount() const { return parameters.getCount(); }
				inline ParameterPtr getParameter( int index ) { return index < parameters.getCount() ? parameters[index] : ParameterPtr::null; }
			};

			class NEUTRON_CORE RenderTextureNode : public RenderNode
			{
				int textureType;
				int width;
				int height;
				int depth;
				int64 format;
				int arraySize;
				int sampleCount;
				int sampleQuality;
				int accessHint;

			public:
				static RenderNodePtr createRenderTextureNode();
				static RenderNodePtr createRenderTextureNode( const FileJson::Value& jvalue, int textureType );
				RenderTextureNode();
				virtual ~RenderTextureNode();
			};

			class NEUTRON_CORE RenderSamplerNode : public RenderNode
			{
				int filterType;

			public:
				static RenderNodePtr createRenderSamplerNode();
				static RenderNodePtr createRenderSamplerNode( const FileJson::Value& jvalue );
				RenderSamplerNode();
				virtual ~RenderSamplerNode();
			};

			class NEUTRON_CORE RenderShaderNode : public RenderNode
			{
				String path;
				String entry;

			public:
				static RenderNodePtr createRenderShaderNode();
				static RenderNodePtr createRenderShaderNode( const FileJson::Value& jvalue, int shaderType );
				RenderShaderNode();
				virtual ~RenderShaderNode();

				void setPath( const char* str ) { path = str; }
				const char* getPath() const { return path.getCStr(); }
				void setEntry( const char* str ) { entry = str; }
				const char* getEntry() const { return entry.getCStr(); }
			};

			class NEUTRON_CORE RenderPipelineNode : public RenderNode
			{
				Array<RenderNodePtr>	childs;
				Array<ParameterPtr>		parameters;

			public:
				static RenderNodePtr createRenderPipelineNode();
				static RenderNodePtr createRenderPipelineNode( const FileJson::Value& jvalue );
				RenderPipelineNode();
				virtual ~RenderPipelineNode();

				void addChild( RenderNodePtr node ) { childs.add( node ); }
				void removeChild( int index ) { if( index < childs.getCount() ) { childs.removeAtFast( index ); } }
				inline int getChildCount() const { return childs.getCount(); }
				inline RenderNodePtr getChild( int index ) { return index < childs.getCount() ? childs[index] : RenderNodePtr::null; }

				void addParameter( ParameterPtr parameter ) { parameters.add( parameter ); }
				void removeParameter( int index ) { if( index < parameters.getCount() ) { parameters.removeAtFast( index ); } }
				inline int getParameterCount() const { return parameters.getCount(); }
				inline ParameterPtr getParameter( int index ) { return index < parameters.getCount() ? parameters[index] : ParameterPtr::null; }
			};
		}
	}
}