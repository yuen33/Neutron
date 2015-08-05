#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronFoundation/Timer.h"

#include "NeutronSystem/NeutronSystem.h"
#include "NeutronSystem/NeutronEngine.h"
#include "NeutronSystem/RenderDevice.h"
#include "NeutronSystem/Window.h"
#include "NeutronSystem/Renderer.h"
#include "NeutronSystem/ProcessingModule.h"

using Neutron::Utility::Timer;
using namespace Neutron::System;
using namespace Neutron::Engine;

int main(int argc, char** argv)
{
	getSystem().init();
	{
		Timer timer;

		ProcessingUnitPtr window = getEngine().getProcessingUnitManager().createWindow( 1024, 768, "test window", false );
		ProcessingUnitPtr renderer = getEngine().getProcessingUnitManager().createRenderer();
		if( !window.isNull() && !renderer.isNull() )
		{
			PinPtr pinWindow = renderer->getPin( "window" );
			if( !pinWindow.isNull() )
			{
				pinWindow->attach( window );
			}

			ProcessingModulePtr module = staticCast<ProcessingModule>( getEngine().getProcessingUnitManager().createProcessingModule() );
			module->addChild( renderer );
			module->addChild( window );
		
			getEngine().runModule( module );
		}

		printf( "%u ms elapsed\n", timer.elapsedMS() );
	}
	getSystem().release();

	system( "pause" );
}