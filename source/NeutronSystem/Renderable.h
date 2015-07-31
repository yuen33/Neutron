#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/HashMap.h"
#include "Resource.h"
#include "Variable.h"

using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class RenderParameter;
			typedef RCPtr<RenderParameter> RenderParameterPtr;

			class NEUTRON_CORE RenderParameter : public RCObject
			{
				String			name;
				String			semantic;
				VariablePtr		value;

			public:
				static RenderParameterPtr create();
				static RenderParameterPtr create( const char* name, const char* semantic, VariablePtr value );

				RenderParameter();
				RenderParameter( const char* name, const char* semantic, VariablePtr value );
				RenderParameter( const RenderParameter& other );
				virtual ~RenderParameter();

				RenderParameter& operator=( RenderParameter& rhs );

				inline void setName( const char* name ) { this->name = name; }
				inline const char* getName() const { return name.getCStr(); }

				inline void setSemantic( const char* semantic ) { this->semantic = semantic; }
				inline const char* getSemantic() const { return semantic.getCStr(); }

				inline void setValue( VariablePtr value ) { this->value = value; }
				inline VariablePtr getValue() const { return value; }
			};

			class NEUTRON_CORE Renderable : public Resource
			{
				struct Parameter
				{
					String			name;
					String			semantic;
					VariablePtr		value;

					Parameter( const char* name, const char* semantic, VariablePtr value )
						: name( name )
						, semantic( semantic )
						, value( value )
					{
					}
				};

				HashMap<uint32, RenderParameterPtr>			nameIndex;
				HashMap<uint32, RenderParameterPtr>			semanticIndex;

			public:
				static RenderablePtr create( Device* owner );
				Renderable( Device* owner );
				virtual ~Renderable();

				void setParameter( const char* name, const char* semantic, VariablePtr value );
				void removeParameterByName( const char* name );
				void removeParameterBySemantic( const char* name );

				RenderParameterPtr getParameterByName( const char* name );
				RenderParameterPtr getParameterBySemantic( const char* semantic );
			};
		}
	}
}