#include "NeutronSystem/Shader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class ShaderD3D11 : public Shader
			{
				ID3D11DeviceChild*	d3dShader;
				uint32				inputSignature;
				uint32				outputSignature;
				void*				binaryCode;
				Size				binaryCodeSize;
				ShaderInfo			shaderInfo;

				boolean compileShader( const char* charCode, Size size, const char* entry );
				boolean createShader( void* binaryCode, Size size );
				void fillShaderInfo( void* binaryCode, Size size );
				boolean initShader( int shaderType, const char* charCode, Size size, const char* entry, const char* include, const char* includePath );

				// debug
				void printShaderInfo();

			public:
				static ShaderPtr createShader( Device* owner );
				ShaderD3D11( Device* owner );
				virtual ~ShaderD3D11();

				inline boolean initVertexShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
				{
					return initShader( ST_VertexShader, charCode, size, entry, include, includePath );
				}
				inline boolean initHullShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
				{
					return initShader( ST_HullShader, charCode, size, entry, include, includePath );
				}
				inline boolean initDomainShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
				{
					return initShader( ST_DomainShader, charCode, size, entry, include, includePath );
				}
				inline boolean initGeometryShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
				{
					return initShader( ST_GeometryShader, charCode, size, entry, include, includePath );
				}
				inline boolean initPixelShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
				{
					return initShader( ST_PixelShader, charCode, size, entry, include, includePath );
				}
				inline boolean initComputeShader( const char* charCode, Size size, const char* entry, const char* include, const char* includePath )
				{
					return initShader( ST_ComputeShader, charCode, size, entry, include, includePath );
				}
				void release();

				inline const ShaderInfo& getShaderInfo() const { return shaderInfo; }
				inline ID3D11VertexShader* getD3DVertexShader() { return shaderType == ST_VertexShader ? static_cast<ID3D11VertexShader*>( d3dShader ) : 0; }
				inline ID3D11HullShader* getD3DHullShader() { return shaderType == ST_HullShader ? static_cast<ID3D11HullShader*>( d3dShader ) : 0; }
				inline ID3D11DomainShader* getD3DDomainShader() { return shaderType == ST_DomainShader ? static_cast<ID3D11DomainShader*>( d3dShader ) : 0; }
				inline ID3D11GeometryShader* getD3DGeometryShader() { return shaderType == ST_GeometryShader ? static_cast<ID3D11GeometryShader*>( d3dShader ) : 0; }
				inline ID3D11PixelShader* getD3DPixelShader() { return shaderType == ST_PixelShader ? static_cast<ID3D11PixelShader*>( d3dShader ) : 0; }
				inline ID3D11ComputeShader* getD3DComputeShader() { return shaderType == ST_ComputeShader ? static_cast<ID3D11ComputeShader*>( d3dShader ) : 0; }
			};
		}
	}
}