#include "ShaderD3D11.h"
#include "NeutronSystem/Log.h"
#include "RenderDeviceD3D11/RenderDeviceD3D11.h"
#include "NeutronFoundation/Hash.h"

using namespace Neutron::System;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			ShaderPtr ShaderD3D11::createShader( Device* owner )
			{
				return ShaderPtr( new ShaderD3D11( owner ) );
			}

			ShaderD3D11::ShaderD3D11( Device* owner )
				: Shader( owner )
			{
			}

			ShaderD3D11::~ShaderD3D11()
			{
			}

			void ShaderD3D11::release()
			{
			}

			boolean ShaderD3D11::compileShader( const char* charCode, Size size, const char* entry )
			{
				static const char* targets[7] = { "", "vs_5_0", "hs_5_0", "ds_5_0", "gs_5_0", "ps_5_0", "cs_5_0" };
				ID3DBlob* binaryCodeBlob;
				ID3DBlob* errorMessageBlob;

#ifdef NEUTRON_DEBUG
				UINT flag0 = D3DCOMPILE_DEBUG;
#else
				UINT flag0 = 0;
#endif
				HRESULT hr = D3DCompile( charCode, size, 0, 0, 0, entry, targets[shaderType], flag0, 0, &binaryCodeBlob, &errorMessageBlob );
				if( FAILED( hr ) )
				{
					Log::error( "ShaderD3D11", "compile shader failed:\n\t%s\n", static_cast<char*>( errorMessageBlob->GetBufferPointer() ) );
					return false;
				}

				binaryCodeSize = binaryCodeBlob->GetBufferSize();
				if( binaryCodeSize > 0 )
				{
					binaryCode = new uint8[binaryCodeSize];
					assert( binaryCode );
					if( binaryCode )
					{
						memcpy( binaryCode, binaryCodeBlob->GetBufferPointer(), binaryCodeSize );
					}
				}

				if( binaryCodeBlob )
				{
					binaryCodeBlob->Release();
				}

				if( errorMessageBlob )
				{
					errorMessageBlob->Release();
				}

				return true;
			}

			boolean ShaderD3D11::createShader( void* binaryCode, Size size )
			{
				if( !owner || !binaryCode || size == 0 )
				{
					return false;
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				HRESULT hr = S_OK;

				switch( shaderType )
				{
					case ST_VertexShader:
					{
						ID3D11VertexShader* shader = 0;
						hr = d3dDevice->CreateVertexShader( binaryCode, size, 0, &shader );
						if( SUCCEEDED( hr ) )
						{
							d3dShader = shader;
						}
					}
					break;
					case ST_HullShader:
					{
						ID3D11HullShader* shader = 0;
						hr = d3dDevice->CreateHullShader( binaryCode, size, 0, &shader );
						if( SUCCEEDED( hr ) )
						{
							d3dShader = shader;
						}
					}
					break;
					case ST_DomainShader:
					{
						ID3D11DomainShader* shader = 0;
						hr = d3dDevice->CreateDomainShader( binaryCode, size, 0, &shader );
						if( SUCCEEDED( hr ) )
						{
							d3dShader = shader;
						}
					}
					break;
					case ST_GeometryShader:
					{
						ID3D11GeometryShader* shader = 0;
						hr = d3dDevice->CreateGeometryShader( binaryCode, size, 0, &shader );
						if( SUCCEEDED( hr ) )
						{
							d3dShader = shader;
						}
					}
					break;
					case ST_PixelShader:
					{
						ID3D11PixelShader* shader = 0;
						hr = d3dDevice->CreatePixelShader( binaryCode, size, 0, &shader );
						if( SUCCEEDED( hr ) )
						{
							d3dShader = shader;
						}
					}
					break;
					case ST_ComputeShader:
					{
						ID3D11ComputeShader* shader = 0;
						hr = d3dDevice->CreateComputeShader( binaryCode, size, 0, &shader );
						if( SUCCEEDED( hr ) )
						{
							d3dShader = shader;
						}
					}
					break;
					default:
					{
					}
				}

				return SUCCEEDED( hr );
			}

			void ShaderD3D11::fillShaderInfo( void* binaryCode, Size size )
			{
				if( !owner || !binaryCode || size == 0 )
				{
					return;
				}

				RenderDeviceD3D11* rd = static_cast<RenderDeviceD3D11*>( owner );
				ID3D11Device* d3dDevice = rd->getD3DDevice();
				ID3D11DeviceContext* d3dContext = rd->getD3DContext();

				ID3D11ShaderReflection* reflection = 0;
				HRESULT hr = D3DReflect( binaryCode, size, IID_ID3D11ShaderReflection, (void**)&reflection );

				D3D11_SHADER_DESC desc;
				hr = reflection->GetDesc( &desc );

				// input parameters
				for( UINT i = 0; i < desc.InputParameters; ++i )
				{
					D3D11_SIGNATURE_PARAMETER_DESC inputParameterDesc;
					hr = reflection->GetInputParameterDesc( i, &inputParameterDesc );

					ShaderParameterInfo* info = new ShaderParameterInfo();
					assert( info );
					info->semanticName = inputParameterDesc.SemanticName;
					info->semanticIndex = (int)inputParameterDesc.SemanticIndex;
					info->registerIndex = (int)inputParameterDesc.Register;
					info->componentDataType = (int)inputParameterDesc.ComponentType;

					shaderInfo.inputParameterInfo.add( info );

					uint32 seed = Math::Hash::range( inputParameterDesc.SemanticName, inputParameterDesc.SemanticName + String::getCStrCount( inputParameterDesc.SemanticName ) );
					Math::Hash::combine( seed, inputParameterDesc.SemanticIndex );
					Math::Hash::combine( seed, inputParameterDesc.Register );
					Math::Hash::combine( seed, static_cast<uint32>( inputParameterDesc.SystemValueType ) );
					Math::Hash::combine( seed, static_cast<uint32>( inputParameterDesc.ComponentType ) );
					Math::Hash::combine( seed, inputParameterDesc.Mask );
					Math::Hash::combine( seed, inputParameterDesc.ReadWriteMask );
					Math::Hash::combine( seed, inputParameterDesc.Stream );
					Math::Hash::combine( seed, inputParameterDesc.MinPrecision );
					Math::Hash::combine( inputSignature, seed );
				}

				// output parameters
				for( UINT i = 0; i < desc.OutputParameters; ++i )
				{
					D3D11_SIGNATURE_PARAMETER_DESC outputParameterDesc;
					hr = reflection->GetOutputParameterDesc( i, &outputParameterDesc );

					ShaderParameterInfo* info = new ShaderParameterInfo();
					assert( info );
					info->semanticName = outputParameterDesc.SemanticName;
					info->semanticIndex = (int)outputParameterDesc.SemanticIndex;
					info->registerIndex = (int)outputParameterDesc.Register;
					info->componentDataType = (int)outputParameterDesc.ComponentType;

					shaderInfo.outputParameterInfo.add( info );

					uint32 seed = Math::Hash::range( outputParameterDesc.SemanticName, outputParameterDesc.SemanticName + String::getCStrCount( outputParameterDesc.SemanticName ) );
					Math::Hash::combine( seed, outputParameterDesc.SemanticIndex );
					Math::Hash::combine( seed, outputParameterDesc.Register );
					Math::Hash::combine( seed, static_cast<uint32>( outputParameterDesc.SystemValueType ) );
					Math::Hash::combine( seed, static_cast<uint32>( outputParameterDesc.ComponentType ) );
					Math::Hash::combine( seed, outputParameterDesc.Mask );
					Math::Hash::combine( seed, outputParameterDesc.ReadWriteMask );
					Math::Hash::combine( seed, outputParameterDesc.Stream );
					Math::Hash::combine( seed, outputParameterDesc.MinPrecision );
					Math::Hash::combine( outputSignature, seed );
				}

				// const buffers
				for( UINT i = 0; i < desc.ConstantBuffers; ++i )
				{
					ID3D11ShaderReflectionConstantBuffer* constBuffer = reflection->GetConstantBufferByIndex( i );

					D3D11_SHADER_BUFFER_DESC desc;
					hr = constBuffer->GetDesc( &desc );

					ShaderConstBufferInfo* constBufferInfo = new ShaderConstBufferInfo();
					assert( constBufferInfo );
					constBufferInfo->name = desc.Name;
					constBufferInfo->size = desc.Size;
					constBufferInfo->constBufferType = (int)desc.Type;

					for( UINT j = 0; j < desc.Variables; ++j )
					{
						ID3D11ShaderReflectionVariable* variable = constBuffer->GetVariableByIndex( j );
						D3D11_SHADER_VARIABLE_DESC variableDesc;
						hr = variable->GetDesc( &variableDesc );

						if( variableDesc.uFlags & D3D_SVF_USED )
						{
							ID3D11ShaderReflectionType* variableType = variable->GetType();
							D3D11_SHADER_TYPE_DESC variableTypeDesc;
							hr = variableType->GetDesc( &variableTypeDesc );

							ShaderVariableInfo* variableInfo = new ShaderVariableInfo();
							assert( variableInfo );

							variableInfo->name = variableDesc.Name;
							variableInfo->offset = (int)variableDesc.StartOffset;
							variableInfo->size = variableDesc.Size;
							variableInfo->define.valueClass = (int)variableTypeDesc.Class;
							variableInfo->define.variableType = (int)variableTypeDesc.Type;
							variableInfo->define.offset = (int)variableTypeDesc.Offset;
							variableInfo->define.numOfRow = (int)variableTypeDesc.Rows;
							variableInfo->define.numOfColumn = (int)variableTypeDesc.Columns;
							variableInfo->define.numOfElement = (int)variableTypeDesc.Elements;
							variableInfo->define.numOfMember = (int)variableTypeDesc.Members;

							constBufferInfo->variables.add( variableInfo );
						}
					}

					if( constBufferInfo->variables.any() )
					{
						shaderInfo.constBufferInfo.add( constBufferInfo );
					}
					else
					{
						delete constBufferInfo;
					}
				}

				// other shader resources
				for( UINT i = 0; i < desc.BoundResources; ++i )
				{
					D3D11_SHADER_INPUT_BIND_DESC bindDesc;
					hr = reflection->GetResourceBindingDesc( i, &bindDesc );

					ShaderResourceInfo* info = new ShaderResourceInfo();
					assert( info );
					info->name = bindDesc.Name;
					info->resourceType = (int)bindDesc.Type;
					info->bindPoint = (int)bindDesc.BindPoint;
					info->bindCount = (int)bindDesc.BindCount;
					info->returnType = (int)bindDesc.ReturnType;
					info->dimension = (int)bindDesc.Dimension;

					shaderInfo.resourceInfo.add( info );
				}

				reflection->Release();
			}

			void ShaderD3D11::printShaderInfo()
			{
				Log::debug( "total %u input parameters\n", shaderInfo.inputParameterInfo.getCount() );
				Log::debug( "total %u output parameters\n", shaderInfo.outputParameterInfo.getCount() );
				Log::debug( "total %u const buffers\n", shaderInfo.constBufferInfo.getCount() );
				Log::debug( "total %u resource\n", shaderInfo.resourceInfo.getCount() );

				Log::debug( "Input parameters: -------------------------------------------------------------\n" );
				for( int i = 0; i < shaderInfo.inputParameterInfo.getCount(); ++i )
				{
					ShaderParameterInfo* info = shaderInfo.inputParameterInfo[i];
					Log::debug( "\t semantic = %s, register = %u\n", info->semanticName.getCStr(), info->registerIndex );
				}

				Log::debug( "Output parameters:-------------------------------------------------------------\n" );
				for( int i = 0; i < shaderInfo.outputParameterInfo.getCount(); ++i )
				{
					ShaderParameterInfo* info = shaderInfo.outputParameterInfo[i];
					Log::debug( "\t semantic = %s, register = %u\n", info->semanticName.getCStr(), info->registerIndex );
				}

				Log::debug( "Const buffers: ----------------------------------------------------------------\n" );
				for( int i = 0; i < shaderInfo.constBufferInfo.getCount(); ++i )
				{
					ShaderConstBufferInfo* info = shaderInfo.constBufferInfo[i];
					Log::debug( "\t name = %s, size = %u\n", info->name.getCStr(), info->size );
					for( int j = 0; j < info->variables.getCount(); ++j )
					{
						ShaderVariableInfo* variableInfo = info->variables[j];
						Log::debug( "\t\tvar name = %s, size = %u, offset = %d\n", variableInfo->name.getCStr(), variableInfo->size, variableInfo->offset );
						ShaderVariableDefine& variableDefine = info->variables[j]->define;
						Log::debug( "\t\t\t class = %d, type = %d, row = %d, \n\t\t\t column = %d, element = %d, member = %d\n",
						variableDefine.valueClass, variableDefine.variableType, variableDefine.numOfRow, variableDefine.numOfColumn, variableDefine.numOfElement, variableDefine.numOfMember );
					}
				}

				Log::debug( "Resource: ---------------------------------------------------------------------\n" );
				for( int i = 0; i < shaderInfo.resourceInfo.getCount(); ++i )
				{
					ShaderResourceInfo* info = shaderInfo.resourceInfo[i];
					Log::debug( "\t name = %s, bind_point = %d, bind_count = %d\n", info->name.getCStr(), info->bindPoint, info->bindCount );
				}
			}

			boolean ShaderD3D11::initShader( int shaderType, const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
			{
				this->shaderType = shaderType;

				if( !compileShader( charCode, size, entry ) )
				{
					return false;
				}

				if( !createShader( binaryCode, binaryCodeSize ) )
				{
					return false;
				}

				fillShaderInfo( binaryCode, binaryCodeSize );

				return true;
			}
		}
	}
}