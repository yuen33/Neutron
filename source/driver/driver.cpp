#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronSystem/NeutronSystem.h"
#include "NeutronSystem/RenderDevice.h"

using namespace Neutron::System;

int main(int argc, char** argv)
{
	Neutron::System::getSystem().init();
	{
		RenderDevicePtr rd = staticCast<RenderDevice>( Neutron::System::getSystem().getDeviceManager().createDevice( "RenderDevice.D3D11" ) );
	}
	Neutron::System::getSystem().release();

	system( "pause" );
}