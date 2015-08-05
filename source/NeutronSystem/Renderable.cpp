#include "Renderable.h"
#include "NeutronFoundation/Hash.h"
#include "Parameter.h"

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
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
			
			void Renderable::release()
			{
				nameIndex.clear();
				semanticIndex.clear();
			}

			void Renderable::setParameter( const char* name, const char* semantic, VariablePtr value )
			{
				removeParameterByName( name );
				removeParameterBySemantic( semantic );
				ParameterPtr newParameter = Parameter::createParameter( name, semantic, value );
				if( !newParameter.isNull() )
				{
					nameIndex.add( Math::Hash::DJB32( name ), newParameter );
					semanticIndex.add( Math::Hash::DJB32( semantic ), newParameter );
				}
			}

			void Renderable::removeParameterByName( const char* name )
			{
				ParameterPtr parameter = getParameterByName( name );
				if( parameter )
				{
					nameIndex.remove( Math::Hash::DJB32( parameter->getName() ) );
					semanticIndex.remove( Math::Hash::DJB32( parameter->getSemantic() ) );

					delete parameter;
				}
			}

			void Renderable::removeParameterBySemantic( const char* name )
			{
				ParameterPtr parameter = getParameterByName( name );
				if( !parameter.isNull() )
				{
					nameIndex.remove( Math::Hash::DJB32( parameter->getName() ) );
					semanticIndex.remove( Math::Hash::DJB32( parameter->getSemantic() ) );

					delete parameter;
				}
			}

			ParameterPtr Renderable::getParameterByName( const char* name )
			{
				HashMap<uint32, ParameterPtr>::Iterator it = nameIndex.find( Math::Hash::DJB32( name ) );
				if( it != nameIndex.end() )
				{
					return it.value();
				}

				return 0;
			}

			ParameterPtr Renderable::getParameterBySemantic( const char* semantic )
			{
				HashMap<uint32, ParameterPtr>::Iterator it = semanticIndex.find( Math::Hash::DJB32( semantic ) );
				if( it != semanticIndex.end() )
				{
					return it.value();
				}

				return 0;
			}
		}
	}
}