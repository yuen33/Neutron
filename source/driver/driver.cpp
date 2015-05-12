#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronSystem/NeutronSystem.h"
using namespace Neutron;
using Neutron::System::NeutronSystem;
using Neutron::System::getSystem;

int main(int argc, char** argv)
{
	getSystem().init();
	getSystem().release();

	system( "pause" );
}