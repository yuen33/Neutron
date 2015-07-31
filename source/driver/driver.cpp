#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronSystem/NeutronSystem.h"
#include "NeutronSystem/NeutronEngine.h"

#include "NeutronFoundation/Timer.h"

using namespace Neutron::System;
using namespace Neutron::Engine;
using Neutron::Utility::Timer;

int main(int argc, char** argv)
{
	getSystem().init();
	{
		Timer timer;

		printf( "%u ms elapsed\n", timer.elapsedMS() );
	}
	getSystem().release();

	system( "pause" );
}