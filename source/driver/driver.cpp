#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronSystem/NeutronSystem.h"
#include "NeutronFoundation/TaskManager.h"
#include "NeutronFoundation/Timer.h"

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
		stopCount = 0;
		//printf( "task %d: OnStart\n", x );
	}

	virtual void onUpdate()
	{
		//printf( "task %d: OnUpdate\n", x );
	}

	virtual void onStop()
	{
		//printf( "task %d: OnStop\n", x );
		//++stopCount;
		//assert( stopCount == 1 );
	}

	virtual void onAbort()
	{
		//printf( "task %d: OnAbort\n", x );
	}
};

int main(int argc, char** argv)
{
	getSystem().init();
	{
		static const int scale = 10000;
		TestTask* tasks[scale];

		for( int i = 0; i < scale; ++i )
		{
			tasks[i] = new TestTask( i );
		}

		Timer timer;
		for( int i = 0; i < scale; ++i )
		{
			while( !getSystem().getTaskManager().assign( tasks[i] ) );
			{
				//printf( "%u assigned", i );
			}
			//while( !getSystem().getTaskManager().assign( &task1 ) );
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