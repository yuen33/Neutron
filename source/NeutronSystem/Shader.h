#pragma once

#include "Resource.h"
#include "NeutronFoundation/String.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Shader : public Resource
			{
			public:
				// shader type
				enum : int
				{
					ST_Unknown,
					ST_VertexShader,
					ST_HullShader,
					ST_DomainShader,
					ST_GeometryShader,
					ST_PixelShader,
					ST_ComputeShader
				};

				struct ShaderParameterInfo
				{
					String		semanticName;
					int			semanticIndex;
					int			registerIndex;
					int			componentDataType;
				};

				struct ShaderVariableDefine
				{
					int			valueClass;
					int			variableType;
					int			numOfRow;
					int			numOfColumn;
					int			numOfElement;
					int			numOfMember;
					int			offset;
				};

				struct ShaderVariableInfo
				{
					String						name;
					int							offset;
					Size						size;
					ShaderVariableDefine		define;
				};

				struct ShaderConstBufferInfo
				{
					String						name;
					int							constBufferType;
					Size						size;
					Array<ShaderVariableInfo*>	variables;
				};

				struct ShaderResourceInfo
				{
					String						name;
					int							resourceType;
					int							bindPoint;
					int							bindCount;
					int							returnType;
					int							dimension;
					int							numOfSamples;
				};

				struct ShaderInfo
				{
					Array<ShaderParameterInfo*>		inputParameterInfo;
					Array<ShaderParameterInfo*>		outputParameterInfo;
					Array<ShaderConstBufferInfo*>	constBufferInfo;
					Array<ShaderResourceInfo*>		resourceInfo;
				};
				
			protected:
				int shaderType;

			public:
				static ShaderPtr createShader( Device* owner );

				Shader( Device* owner );
				virtual ~Shader();

				inline int getShaderType() const { return shaderType; }
			};
		}
	}
}