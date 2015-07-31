#include "Renderable.h"
#include "NeutronFoundation/Hash.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			// render parameter
			RenderParameterPtr RenderParameter::create()
			{
				return RenderParameterPtr( new RenderParameter() );
			}

			RenderParameterPtr RenderParameter::create( const char* name, const char* semantic, VariablePtr value )
			{
				return RenderParameterPtr( new RenderParameter( name, semantic, value ) );
			}

			RenderParameter::RenderParameter()
			{
			}

			RenderParameter::RenderParameter( const char* name, const char* semantic, VariablePtr value )
				: name( name )
				, semantic( semantic )
				, value( value )
			{
			}

			RenderParameter::RenderParameter( const RenderParameter& other )
				: name( other.name )
				, semantic( other.semantic )
				, value( other.value )
			{
			}

			RenderParameter::~RenderParameter()
			{
			}

			RenderParameter& RenderParameter::operator=( RenderParameter& rhs )
			{
				this->name = rhs.name;
				this->semantic = rhs.semantic;
				this->value = rhs.value;
				return *this;
			}
			
			// renderable
			RenderablePtr Renderable::create( Device* owner )
			{
				return RenderablePtr( new Renderable( owner ) );
			}

			Renderable::Renderable( Device* owner )
				: Resource( owner )
			{
			}

			Renderable::~Renderable()
			{
			}

			void Renderable::setParameter( const char* name, const char* semantic, VariablePtr value )
			{
				removeParameterByName( name );
				removeParameterBySemantic( semantic );
				RenderParameterPtr newParameter = RenderParameter::create( name, semantic, value );
				if( !newParameter.isNull() )
				{
					nameIndex.add( Math::Hash::DJB32( name ), newParameter );
					semanticIndex.add( Math::Hash::DJB32( semantic ), newParameter );
				}
			}

			void Renderable::removeParameterByName( const char* name )
			{
				RenderParameterPtr parameter = getParameterByName( name );
				if( parameter )
				{
					nameIndex.remove( Math::Hash::DJB32( parameter->getName() ) );
					semanticIndex.remove( Math::Hash::DJB32( parameter->getSemantic() ) );

					delete parameter;
				}
			}

			void Renderable::removeParameterBySemantic( const char* name )
			{
				RenderParameterPtr parameter = getParameterBySemantic( name );
				if( parameter )
				{
					nameIndex.remove( Math::Hash::DJB32( parameter->getName() ) );
					semanticIndex.remove( Math::Hash::DJB32( parameter->getSemantic() ) );

					delete parameter;
				}
			}

			RenderParameterPtr Renderable::getParameterByName( const char* name )
			{
				HashMap<uint32, RenderParameterPtr>::Iterator it = nameIndex.find( Math::Hash::DJB32( name ) );
				if( it != nameIndex.end() )
				{
					return it.value();
				}

				return 0;
			}

			RenderParameterPtr Renderable::getParameterBySemantic( const char* semantic )
			{
				HashMap<uint32, RenderParameterPtr>::Iterator it = semanticIndex.find( Math::Hash::DJB32( semantic ) );
				if( it != semanticIndex.end() )
				{
					return it.value();
				}

				return 0;
			}
		}
	}
}