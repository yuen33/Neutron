#pragma once

#include "NeutronSystem\NeutronSystem.h"
#include "NeutronFoundation\TCPServer.h"

using Neutron::System::NeutronSystem;
using Neutron::Network::TCPServer;

void testServer()
{
	int counter = 0;

	if( Neutron::System::getSystem().init() )
	{
		Neutron::Network::init();
		TCPServer server;
		if( server.init( &Neutron::System::getSystem().getTaskManager(), "192.168.2.221", 7001, 2048 ) )
		{
			while( true )
			{
				//server.update();
				char line[128] = {'\0'};
				memset( line, 0, 128 );
				sprintf( line, "server count = %d\n", counter++ );
				server.broadcast( ( Neutron::uint8* )line, strlen( line ) + 1 );
			}

			server.release();
		}
		Neutron::Network::release();
		Neutron::System::getSystem().release();
	}
}