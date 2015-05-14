#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronSystem/NeutronSystem.h"
#include "NeutronFoundation/TaskManager.h"

using namespace Neutron;
using Neutron::System::NeutronSystem;
using Neutron::System::getSystem;
using Neutron::Utility::Task;

class TestTask : public Task
{
	String name;
	int stopCount = 0;

public:
	TestTask( const char* name )
		:name( name )
	{
	}

	virtual ~TestTask()
	{
	}

	virtual void onStart()
	{
		printf( "%s: OnStart\n", name.getCStr() );
	}

	virtual void onUpdate()
	{
		printf( "%s: OnUpdate\n", name.getCStr() );
	}

	virtual void onStop()
	{
		printf( "%s: OnStop\n", name.getCStr() );
		++stopCount;
		assert( stopCount == 1 );
	}

	virtual void onAbort()
	{
		printf( "%s: OnAbort\n", name.getCStr() );
	}
};

int main(int argc, char** argv)
{
	getSystem().init();
	{
		TestTask task0( "task0" );
		TestTask task1( "task1" );
		getSystem().getTaskManager().assign( &task0 );
		getSystem().getTaskManager().assign( &task1 );

		getSystem().run();
	}
	getSystem().release();

	system( "pause" );
}