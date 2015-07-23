#pragma once

#include "NeutronSystem\NeutronSystem.h"
#include "NeutronFoundation\TCPClient.h"

using Neutron::System::NeutronSystem;
using Neutron::Network::TCPClient;

void testClient()
{
	int counter = 0;

	if( Neutron::System::getSystem().init() )
	{
		Neutron::Network::init();
		TCPClient client;
		if( client.init( &Neutron::System::getSystem().getTaskManager(), "192.168.2.221", 7001, 2048 ) )
		{
			while( true )
			{
				//client.update();
				char line[128] = { '\0' };
				memset( line, 0, 128 );
				sprintf( line, "client count = %d\n", counter++ );
				client.send( ( Neutron::uint8* )line, strlen( line ) + 1 );
			}
			client.release();
		}
		Neutron::Network::release();
		Neutron::System::getSystem().release();
	}
}