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
			TaskRunner* runner = reinterpret_cast< TaskRunner* >( args );

			while( !runner->owner->getExitFlag() )
			{
				if( runner->getTask() == 0 )
				{
					runner->owner->assignRunnersToTasks( runner );
				}

				Task* task = runner->getTask();
				if( task )
				{
					if( !task->getAbortFlag() )
					{
						switch( task->getState() )
						{
							case Task::Pending:
							{
								task->setState( Task::Running );
								task->onStart();
								task->setState( task->getUpdateFlag() ? Task::Running : Task::Ending );
							}
							break;
							case Task::Running:
							{
								task->onUpdate();
								task->setState( task->getUpdateFlag() ? Task::Running : Task::Ending );
							}
							break;
							case Task::Ending:
							{
								task->onStop();
								task->setState( Task::Ended );
							}
							break;
							default:
							{
								printf( "Invalid Task state = %d\n", task->getState() );
								//assert( 0 );
							}
						}
					}
					//else
					//{
					//	switch( task->getState() )
					//	{
					//		case Task::Pending:
					//		{
					//			task->setState( Task::Ended );
					//		}
					//		break;
					//		case Task::Running:
					//		case Task::Ending:
					//		{
					//			task->onAbort();
					//			task->setState( Task::Ended );
					//		}
					//		break;
					//		default:
					//		{
					//			printf( "Task state = %d", task->getState() );
					//			//assert( 0 );
					//		}
					//	}
					//}
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
			, exitEvent( true, false )
			, exitFlag( false )
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
					while( !pendingTasks.pop( task ) );
					if( task )
					{
						task->onAbort();
						task->setState( Task::Ended );
					}
					/*if( task )
					{
						task->abort();
					}*/

					// if task started, push back to pending queue, let runners run the custom abort()
					// if not started, drop it
					/*if( task->getState() != Task::Pending )
					{
						pendingTasks.push( task );
					}*/
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

			exitEvent.set();
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

		void TaskManager::waitForTask()
		{
			NEUTRON_EVENT events[2];
			events[0] = pendingTaskEvent.getHandle();
			events[1] = exitEvent.getHandle();
			waitEvents( events, 2, false, NEUTRON_WAIT_TIME_INFINITE );
		}

		boolean TaskManager::assign( Task* task )
		{
			if( task != 0 && task->getState() == Task::Initialized )
			{
				if( pendingTasks.push( task ) )
				{
					task->setState( Task::Pending );
					pendingTaskEvent.set();
					atomIncrement32( &assignedTasks );
					return true;
				}
			}

			return false;
		}

		void TaskManager::assignRunnersToTasks( TaskRunner* runner )
		{
			waitForTask();

			// if there is pending tasks and idle runners
			if( pendingTasks.any() )
			{
				Task* task = 0;
				if( pendingTasks.pop( task ) && task )
				{
					assert( task->getState() == Task::Pending || task->getState() == Task::Running || task->getState() == Task::Ending );
					runner->setTask( task );
					//printf( "[%u] runner %d assigned to task %p state = %d\n", timer.elapsedUS(), runner->getId(), task, task->getState() );
				}
			}
		}

		void TaskManager::releaseRunnerFromTasks( TaskRunner* runner )
		{
			Task* task = runner->getTask();
			if( task )
			{
				if( task->getState() != Task::Ended )
				{
					assert( pendingTasks.push( task ) );
				}
				else
				{
					atomIncrement32( &finishedTasks );
				}
			}

			if( !exitFlag && pendingTasks.any() )
			{
				pendingTaskEvent.set();
			}
			else
			{
				pendingTaskEvent.reset();
			}

			runner->setTask( 0 );
		}
	}
}