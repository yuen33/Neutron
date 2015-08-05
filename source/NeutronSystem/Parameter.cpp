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

		ParameterPtr Parameter::createParameter( const char* name, const char* semantic, VariablePtr value )
		{
			return ParameterPtr( new Parameter( name, semantic, value ) );
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