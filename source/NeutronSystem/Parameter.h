#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/String.h"
#include "Variable.h"
#include "NeutronFoundation/FileJson.h"

using Neutron::Container::String;
using Neutron::Utility::FileJson;

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE Parameter : public RCObject
		{
			String			name;
			String			semantic;
			VariablePtr		value;

		public:
			static ParameterPtr createParameter();
			static ParameterPtr createParameter( const char* name, const char* semantic, VariablePtr value );
			static ParameterPtr createParameter( const FileJson::Value& jvalue );

			Parameter();
			Parameter( const char* name, const char* semantic, VariablePtr value );
			Parameter( const Parameter& other );
			virtual ~Parameter();

			Parameter& operator=( Parameter& rhs );

			inline void setName( const char* name ) { this->name = name; }
			inline const char* getName() const { return name.getCStr(); }

			inline void setSemantic( const char* semantic ) { this->semantic = semantic; }
			inline const char* getSemantic() const { return semantic.getCStr(); }

			inline void setValue( VariablePtr value ) { this->value = value; }
			inline VariablePtr getValue() const { return value; }
		};
	}
}