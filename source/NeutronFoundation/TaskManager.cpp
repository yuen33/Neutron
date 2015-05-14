#include "TaskManager.h"
#include "Array.h"
using Neutron::Container::Array;

namespace Neutron
{
	namespace Utility
	{
		// task
		Task::Task()
			:state( Initialized )
			, updateFlag( false )
		{
		}

		Task::~Task()
		{
		}

		void Task::onStart()
		{
		}

		void Task::onUpdate()
		{
		}

		void Task::onStop()
		{
		}

		void Task::onAbort()
		{
		}

		// task runner
		TaskRunner::TaskRunner( TaskManager* owner )
			:owner( owner )
			, task( task )
		{
			assert( owner );
		}

		TaskRunner::~TaskRunner()
		{
		}

		boolean TaskRunner::init()
		{
			if( SimpleThread::init( process, this ) )
			{
				start();
				return true;
			}

			return false;
		}

		void TaskRunner::release()
		{
			SimpleThread::release();
		}

		uint32 __stdcall TaskRunner::process( void* args )
		{
			assert( args );
			TaskRunner* runner = reinterpret_cast<TaskRunner*>( args );
			Task* task = runner->getTask();

			while( !runner->owner->getExitFlag() )
			{
				if( task == 0 )
				{
					runner->owner->assignRunnersToTasks( runner );
					task = runner->getTask();
				}
				else
				{
					if( !task->getAbortFlag() )
					{
						if( task->getState() == Task::Pending )
						{
							task->setState( Task::Running );
							task->onStart();
							task->setState( task->getUpdateFlag() ? Task::Running : Task::Ending );
						}
						else if( task->getState() == Task::Running && task->getUpdateFlag() )
						{
							task->onUpdate();
							task->setState( task->getUpdateFlag() ? Task::Running : Task::Ending );
						}
						else if( task->getState() == Task::Ending )
						{
							task->onStop();
							task->setState( Task::Ended );
						}
					}
					else
					{
						if( task->getState() == Task::Pending )
						{
							task->setState( Task::Ended );
						}
						else if( task->getState() != Task::Ended )
						{
							task->onAbort();
							task->setState( Task::Ended );
						}
					}
				}

				runner->owner->releaseRunnerFromTasks( runner );
			}

			return 0;
		}

		void onAbort()
		{
		}

		// task manager
		TaskManager::TaskManager()
			:pendingTaskEvent( true, false )
			,exitEvent( false, false )
			,exitFlag( false )
		{
		}

		TaskManager::~TaskManager()
		{
		}

		boolean TaskManager::init( int runnerCount, int taskCapacity )
		{
			// prepare queues
			runners.reserve( runnerCount );
			pendingTasks.reserve( taskCapacity );

			// create runners
			for( int i = 0; i < runnerCount; ++i )
			{
				TaskRunner* newRunner = new TaskRunner( this );
				assert( newRunner );
				newRunner->init();
				runners.add( newRunner );
			}

			return true;
		}

		void TaskManager::release()
		{
			// set flag, prevent new task assignment
			exitEvent.set();

			//while( idleRunners.getCount() != runners.getCount() )
			while( !isIdle() )
			{
				// check all runners, set all running tasks abort
				for( int i = 0; i < runners.getCount(); ++i )
				{
					if( runners[i]->isRunning() )
					{
						Task* task = runners[i]->getTask();
						if( task && task->getState() != Task::Ended )
						{
							task->abort();
						}
					}
				}

				// set all pending tasks abort
				int pendingCount = pendingTasks.getCount();
				for( int i = 0; i < pendingCount; ++i )
				{
					Task* task = 0;
					pendingTasks.pop( task );
					if( task )
					{
						task->abort();
					}

					// if task started, push back to pending queue, let runners run the custom abort()
					// if not started, drop it
					if( task->getState() != Task::Pending )
					{
						pendingTasks.push( task );
					}
				}

				// let remain tasks run out
				//assignRunnersToTasks();
			}

			// release threads
			Array<NEUTRON_THREAD_HANDLE> threads;
			for( int i = 0; i < runners.getCount(); ++i )
			{
				threads.add( runners[i]->getHandle() );
			}
			exitFlag = true;
			waitThreads( threads.getData(), threads.getCount(), true, NEUTRON_WAIT_TIME_INFINITE );

			for( int i = 0; i < runners.getCount(); ++i )
			{
				runners[i]->release();
				delete runners[i];
				runners[i] = 0;
			}
			runners.clear();
		}

		void TaskManager::update()
		{

			/*if( !exitFlag )
			{
			assignRunnersToTasks();
			}*/
		}

		void TaskManager::waitForTask()
		{
			NEUTRON_EVENT events[2];
			events[0] = pendingTaskEvent.getHandle();
			events[1] = exitEvent.getHandle();
			waitEvents( events, 2, false, NEUTRON_WAIT_TIME_INFINITE );
			//waitEvent( newTaskEvent.getHandle(), NEUTRON_WAIT_TIME_INFINITE );
		}

		boolean TaskManager::assign( Task* task )
		{
			if( task != 0 && task->getState() == Task::Initialized )
			{
				if( pendingTasks.push( task ) )
				{
					task->setState( Task::Pending );
					pendingTaskEvent.set();
					return true;
				}
			}

			return false;
		}

		void TaskManager::assignRunnersToTasks( TaskRunner* runner )
		{
			/*NEUTRON_EVENT events[2];
			events[0] = getNewTaskEvent().getHandle();
			events[1] = getExitEvent().getHandle();
			waitEvents( events, 2, false, NEUTRON_WAIT_TIME_INFINITE );*/ 

			waitForTask();

			//printf( "assignRunnersToTasks\n" );

			// if there is pending tasks and idle runners
			while( pendingTasks.any() )
			{
				Task* task = 0;
				pendingTasks.pop( task );
				if( task )
				{
					++activeRunners;
					runner->setTask( task );
				}
			}
		}

		void TaskManager::releaseRunnerFromTasks( TaskRunner* runner )
		{
			//printf( "releaseRunnerFromTasks\n" );

			Task* task = runner->getTask();
			if( task )
			{
				if( task->getState() != Task::Ended )
				{
					pendingTasks.push( task );
					pendingTaskEvent.set();
				}
				else if( pendingTasks.empty() )
				{
					pendingTaskEvent.reset();
				}

				--activeRunners;
			}

			runner->setTask( 0 );
			//idleRunners.push( runner );
			//runner->suspend();
		}
	}
}