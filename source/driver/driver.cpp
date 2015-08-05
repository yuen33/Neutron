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

		WindowPtr window = getEngine().getProcessingUnitManager().createWindow( 1024, 768, "test window", false );
		RendererPtr renderer = getEngine().getProcessingUnitManager().createRenderer();
		if( !window.isNull() && !renderer.isNull() )
		{
			PinPtr pinWindow = renderer->getPin( "window" );
			if( !pinWindow.isNull() )
			{
				pinWindow->attach( staticCast<ProcessingUnit>( window ) );
			}

			ProcessingModulePtr module = getEngine().getProcessingUnitManager().createProcessingModule();
			module->addChild( staticCast<ProcessingUnit>( renderer ) );
			module->addChild( staticCast<ProcessingUnit>( window ) );
		
			getEngine().runModule( module );
		}

		printf( "%u ms elapsed\n", timer.elapsedMS() );
	}
	getSystem().release();

	system( "pause" );
}