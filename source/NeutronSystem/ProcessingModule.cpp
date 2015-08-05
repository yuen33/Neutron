#include "ProcessingModule.h"

namespace Neutron
{
	namespace Engine
	{
		ProcessingUnitPtr ProcessingModule::createProcessingUnitModule( Device* owner )
		{
			return ProcessingUnitPtr( new ProcessingModule( owner ) );
		}

		ProcessingModule::ProcessingModule( Device* owner )
			: ProcessingUnit( owner )
		{
		}

		ProcessingModule::~ProcessingModule( )
		{
		}

		void ProcessingModule::release()
		{
			for( int i = 0; i < childs.getCount(); ++i )
			{
				childs[i]->release();
			}
			childs.clear();
		}

		boolean ProcessingModule::assembleUnit()
		{
			abstractChilds();
			printIdlePins();

			for( int i = 0; i < childs.getCount(); ++i )
			{
				if( !childs[i]->assembleUnit() )
				{
					return false;
				}
			}

			return true;
		}

		boolean ProcessingModule::updateUnit()
		{
			if( childs.getCount() > 0 )
			{
				return childs[0]->updateUnit();
			}

			return false;
		}

		void ProcessingModule::abstractChilds()
		{
			for( int i = 0; i < childs.getCount(); ++i )
			{
				ProcessingUnitPtr unit = childs[i];
				if( unit->getProcessingUnitType() == PUT_Module )
				{
					staticCast<ProcessingModule>( unit )->abstractChilds();
				}

				for( HashMap<uint32, PinPtr>::Iterator itPins = unit->getPins().begin(); itPins != unit->getPins().end(); ++itPins )
				{
					if( itPins.value()->isIdle() )
					{
						pins.add( itPins.key(), itPins.value() );
					}
				}
			}
		}
	}
}