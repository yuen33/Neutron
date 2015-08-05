#include "ProcessingUnit.h"
#include "NeutronFoundation/Hash.h"
#include "NeutronFoundation/String.h"
#include "Log.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace Engine
	{
		ProcessingUnit::ProcessingUnit( Device* owner )
			: owner( owner )
		{
		}

		ProcessingUnit::~ProcessingUnit()
		{
		}

		void ProcessingUnit::deleteMethod( RCObject* object )
		{
			//assert( owner );
			if( owner )
			{
				release();
				delete static_cast<ProcessingUnit*>( object );
			}
			else
			{
				RCObject::deleteMethod( object );
			}
		}

		void ProcessingUnit::registerPin( const char* name, PinPtr pin )
		{
			pins.add( Math::Hash::DJB32( name ), pin );
			pin->setName( name );
		}

		void ProcessingUnit::unregisterPin( const char* name )
		{
			pins.remove( Math::Hash::DJB32( name ) );
		}

		boolean ProcessingUnit::assembleUnit()
		{
			return true;
		}

		boolean ProcessingUnit::updateUnit()
		{
			return true;
		}

		void ProcessingUnit::printIdlePins()
		{
			Array<PinPtr> idlePins;
			getIdlePins( idlePins );
			for( int i = 0; i < idlePins.getCount(); ++i )
			{
				System::Log::warning( "ProcessingUnit", String::format( "pin %s not attached\n", idlePins[i]->getName() ).getCStr() );
			}
		}

		PinPtr ProcessingUnit::getPin( const char* name )
		{
			HashMap<uint32, PinPtr>::Iterator it = pins.find( Math::Hash::DJB32( name ) );
			return it != pins.end() ? it.value() : PinPtr::null;
		}

		void ProcessingUnit::getIdlePins( Array<PinPtr>& idlePins )
		{
			idlePins.clear();
			for( HashMap<uint32, PinPtr>::Iterator itPin = pins.begin(); itPin != pins.end(); ++itPin )
			{
				if( itPin.value()->isIdle() )
				{
					idlePins.add( itPin.value() );
				}
			}
		}
	}
}