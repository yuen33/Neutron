#pragma once

#include "NeutronSystemCommon.h"
#include "ProcessingUnit.h"

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE ProcessingModule : public ProcessingUnit
		{
			Array<ProcessingUnitPtr>						childs;

			void abstractChilds();

		public:
			static ProcessingUnitPtr createProcessingUnitModule( Device* owner );
			ProcessingModule( Device* owner );
			virtual ~ProcessingModule();

			virtual void release();

			virtual boolean assembleUnit();
			virtual boolean updateUnit();

			inline void addChild( ProcessingUnitPtr childUnit ) { childs.add( childUnit ); }
			inline int getChildCount() { return childs.getCount(); }
			inline ProcessingUnitPtr getChild( int index ) { return index < childs.getCount() ? childs[index] : ProcessingUnitPtr::null; }
		};
	}
}