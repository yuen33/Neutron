#include "Parameter.h"

namespace Neutron
{
	namespace Engine
	{
		// render parameter
		ParameterPtr Parameter::createParameter()
		{
			return ParameterPtr( new Parameter() );
		}

		ParameterPtr Parameter::createParameter( const char* name, const char* semantic, VariablePtr variable )
		{
			return ParameterPtr( new Parameter( name, semantic, variable ) );
		}

		ParameterPtr Parameter::createParameter( const FileJson::Value& jvalue )
		{
			VariablePtr variable = VariablePtr::null;
			String variableTypeName = jvalue["variableType"].GetString();
			if( variableTypeName == "boolean" )
			{
				boolean value = FileJson::existBooleanMember( jvalue, "value" ) ? jvalue["value"].GetBool() : false;
				variable = VariablePtr( static_cast<Variable*>( new VarBoolean( value ) ) );
			}
			else if( variableTypeName == "int" )
			{
				int value = FileJson::existInt32Member( jvalue, "value" ) ? jvalue["value"].GetInt() : 0;
				variable = VariablePtr( static_cast<Variable*>( new VarInt( value ) ) );
			}
			else if( variableTypeName == "int64" )
			{
				int value = FileJson::existInt64Member( jvalue, "value" ) ? jvalue["value"].GetInt64() : 0;
				variable = VariablePtr( static_cast<Variable*>( new VarInt64( value ) ) );
			}
			else if( variableTypeName == "uint32" )
			{
				uint32 value = FileJson::existUInt32Member( jvalue, "value" ) ? jvalue["value"].GetUint() : 0U;
				variable = VariablePtr( static_cast<Variable*>( new VarUInt32( value ) ) );
			}
			else if( variableTypeName == "uint64" )
			{
				uint64 value = FileJson::existUInt64Member( jvalue, "value" ) ? jvalue["value"].GetUint64() : 0U;
				variable = VariablePtr( static_cast<Variable*>( new VarUInt64( value ) ) );
			}
			else if( variableTypeName == "float" )
			{
				float value = FileJson::existFloatMember( jvalue, "value" ) ? static_cast<float>( jvalue["value"].GetDouble() ) : 0.0f;
				variable = VariablePtr( static_cast<Variable*>( new VarFloat( value ) ) );
			}
			else if( variableTypeName == "float2" )
			{
				if( FileJson::existFloat2Member( jvalue, "value" ) )
				{
					float2 value = FileJson::read( jvalue["value"], float2::null );
					variable = VariablePtr( static_cast<Variable*>( new VarFloat2( value ) ) );
				}
			}
			else if( variableTypeName == "float3" )
			{
				if( FileJson::existFloat3Member( jvalue, "value" ) )
				{
					float3 value = FileJson::read( jvalue["value"], float3::null );
					variable = VariablePtr( static_cast<Variable*>( new VarFloat3( value ) ) );
				}
			}
			else if( variableTypeName == "float2" )
			{
				if( FileJson::existFloat4Member( jvalue, "value" ) )
				{
					float4 value = FileJson::read( jvalue["value"], float4::null );
					variable = VariablePtr( static_cast<Variable*>( new VarFloat4( value ) ) );
				}
			}
			else if( variableTypeName == "float4x4" )
			{
				if( FileJson::existFloat4x4Member( jvalue, "value" ) )
				{
					float4x4 value = FileJson::read( jvalue["value"], float4x4::null );
					variable = VariablePtr( static_cast<Variable*>( new VarFloat4x4( value ) ) );
				}
			}
			else if( variableTypeName == "double" )
			{
				double value = FileJson::existFloatMember( jvalue, "value" ) ? jvalue["value"].GetDouble() : 0.0;
				variable = VariablePtr( static_cast<Variable*>( new VarDouble( value ) ) );
			}
			else if( variableTypeName == "string" )
			{
				String value = FileJson::existStringMember( jvalue, "value" ) ? jvalue["value"].GetString() : "";
				variable = VariablePtr( static_cast<Variable*>( new VarString( value ) ) );
			}

			const char* name = FileJson::existStringMember( jvalue, "name" ) ? jvalue["name"].GetString() : 0;
			const char* semantic = FileJson::existStringMember( jvalue, "semantic" ) ? jvalue["semantic"].GetString() : 0;

			if( !variable.isNull() && ( name != 0 && name[0] != '\0' || semantic != 0 && semantic[0] != '\0' ) )
			{
				return createParameter( name, semantic, variable );
			}

			return ParameterPtr::null;
		}

		Parameter::Parameter()
		{
		}

		Parameter::Parameter( const char* name, const char* semantic, VariablePtr value )
			: name( name )
			, semantic( semantic )
			, value( value )
		{
		}

		Parameter::Parameter( const Parameter& other )
			: name( other.name )
			, semantic( other.semantic )
			, value( other.value )
		{
		}

		Parameter::~Parameter()
		{
		}

		Parameter& Parameter::operator=( Parameter& rhs )
		{
			this->name = rhs.name;
			this->semantic = rhs.semantic;
			this->value = rhs.value;
			return *this;
		}
	}
}