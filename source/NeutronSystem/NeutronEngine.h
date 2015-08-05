#pragma once

#include "NeutronSystemCommon.h"
#include "ResourceManager.h"
#include "ProcessingUnitManager.h"
#include "ProcessingUnit.h"

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE NeutronEngine
		{
			ResourceManager				resourceManager;
			ProcessingUnitManager		processingUnitManager;

		public:
			NeutronEngine();
			virtual ~NeutronEngine();

			boolean init();
			void release();

			void runModule( ProcessingModulePtr module );

			inline ResourceManager& getResourceManager() { return resourceManager; }
			inline ProcessingUnitManager& getProcessingUnitManager() { return processingUnitManager; }
		};

		inline NEUTRON_CORE NeutronEngine& getEngine();
	}
}