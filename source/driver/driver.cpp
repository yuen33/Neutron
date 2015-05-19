#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronSystem/NeutronSystem.h"
#include "NeutronFoundation/TaskManager.h"
#include "NeutronFoundation/Timer.h"
#include "NeutronFoundation/Stream.h"

using namespace Neutron;
using Neutron::System::NeutronSystem;
using Neutron::System::getSystem;
using Neutron::Utility::Task;
using Neutron::Utility::Timer;

class TestTask : public Task
{
	int x;
	int stopCount = 0;

public:
	TestTask( int x )
		:x( x )
	{
	}

	virtual ~TestTask()
	{
	}

	virtual void onStart()
	{
		setUpdateFlag( true );
		stopCount = 0;
		//printf( "task %d, runner %d: OnStart\n", x, getRunnerID() );
	}

	virtual void onUpdate()
	{
		//printf( "task %d, runner %d: onUpdate\n", x, getRunnerID() );
		if( ++stopCount >= 4 )
		{
			stop();
		}
	}

	virtual void onStop()
	{
		//printf( "task %d, runner %d: onStop\n", x, getRunnerID() );
	}

	virtual void onAbort()
	{
		//printf( "task %d, runner %d: onAbort\n", x, getRunnerID() );
	}
};

int main(int argc, char** argv)
{
	getSystem().init();
	{
		static const int scale = 1024;
		TestTask* tasks[scale];

		for( int i = 0; i < scale; ++i )
		{
			tasks[i] = new TestTask( i );
		}

		Timer timer;
		for( int i = 0; i < scale; ++i )
		{
			while( !getSystem().getTaskManager().assign( tasks[i] ) );
		}

		getSystem().run();
		uint64 us = timer.elapsedUS();
		printf( "%u us elapsed, %f us on average\n", us, (float)us / (float)scale );

		for( int i = 0; i < scale; ++i )
		{
			delete tasks[i];
		}
	}
	getSystem().release();

	system( "pause" );
}