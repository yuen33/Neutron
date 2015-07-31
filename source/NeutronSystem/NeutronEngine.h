#pragma once

#include "NeutronSystemCommon.h"
#include "ResourceManager.h"
#include "ProcessingUnitManager.h"

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

			inline ResourceManager& getResourceManager() { return resourceManager; }
			inline ProcessingUnitManager& getProcessingUnitManager() { return processingUnitManager; }
		};

		inline NEUTRON_CORE NeutronEngine& getEngine();
	}
}