#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/String.h"
#include "NeutronFoundation/HashMap.h"

using Neutron::Container::String;
using Neutron::Container::HashMap;
using Neutron::System::Device;


namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE ProcessingUnitManager
		{
		public:
			struct ProcessingUnitInfo
			{
				int processingUnitType;
				String name;
				Device* device;

				ProcessingUnitInfo( int processingUnitType, const char* name, Device* device )
					: processingUnitType( processingUnitType )
					, name( name )
					, device( device )
				{
				}
			};

			HashMap<uint32, ProcessingUnitInfo*>		nameIndex;
			HashMap<int, Array<ProcessingUnitInfo*> >	typeIndex;
			HashMap<int, Array<ProcessingUnit*> >		processingUnits;

			ProcessingUnitInfo* findInfoByProcessingUnitType( int processingUnitType );

		public:
			ProcessingUnitManager();
			virtual ~ProcessingUnitManager();

			void registerProcessingUnit( const char* name, int processingUnitType, Device* device );
			void unregisterProcessingUnit( const char* name );

			// window
			inline WindowPtr createWindow( int width, int height, const char* title, boolean fullscreen );
		};
	}
}