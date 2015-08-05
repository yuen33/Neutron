#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/HashMap.h"
#include "Resource.h"
#include "Parameter.h"

using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Engine
	{
		namespace Render
		{
			class NEUTRON_CORE Renderable : public Resource
			{
				HashMap<uint32, ParameterPtr>			nameIndex;
				HashMap<uint32, ParameterPtr>			semanticIndex;

			public:
				static RenderablePtr create( Device* owner );
				Renderable( Device* owner );
				virtual ~Renderable();

				void release();

				void setParameter( const char* name, const char* semantic, VariablePtr value );
				void removeParameterByName( const char* name );
				void removeParameterBySemantic( const char* name );

				ParameterPtr getParameterByName( const char* name );
				ParameterPtr getParameterBySemantic( const char* semantic );
			};
		}
	}
}