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
			,task( task )
		{
			assert( owner );
		}

		TaskRunner::~TaskRunner()
		{
		}

		boolean TaskRunner::init()
		{
			return SimpleThread::init( process, this );
		}

		void TaskRunner::release()
		{
			SimpleThread::release();
		}

		uint32 __stdcall TaskRunner::process( void* args )
		{
			assert( args );
			TaskRunner* runner = reinterpret_cast<TaskRunner*>( args );
			Task* task = runner->task;

			if( task != 0 )
			{
				if( task->getState() == Task::Ended )
				{
					return 0;
				}

				if( !task->getAbortFlag() )
				{
					if( task->getState() == Task::Pending )
					{
						task->setState( Task::Running );
						task->onStart();
					}
					else if( task->getState() == Task::Running )
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

		void onAbort()
		{
		}

		// task manager
		TaskManager::TaskManager()
			:flushFlag( false )
			, exitFlag( false )
		{
		}

		TaskManager::~TaskManager()
		{
		}

		boolean TaskManager::init( int runnerCount, int taskCapacity )
		{
			// prepare queues
			idleRunners.reserve( runnerCount );
			pendingTasks.reserve( taskCapacity );
			runningTasks.reserve( taskCapacity );

			// create runners
			for( int i = 0; i < runnerCount; ++i )
			{
				TaskRunner* newRunner = new TaskRunner( 0 );
				assert( newRunner );
				idleRunners.push( newRunner );
			}
		}

		void TaskManager::release()
		{
			// set flag
			exitFlag = true;
			// abort all active runners
			
			// flush
			flush();
			// release resources
			Array<NEUTRON_THREAD_ID> threads;

		}

		void TaskManager::update()
		{
			if( !exitFlag )
			{
				assignRunnersToTasks();
			}
		}

		void TaskManager::flush()
		{
			// set flush flag
			flushFlag = true;
			// waiting for all tasks end
			while( pendingTasks.any() && runningTasks.any() );
			// set back flush flag
			flushFlag = false;
		}

		boolean TaskManager::assign( Task* task )
		{
			if( !flushFlag && !exitFlag && task != 0 )
			{
				return pendingTasks.push( task );
			}

			return false;
		}

		void TaskManager::assignRunnersToTasks()
		{
			// if there is pending tasks and idle runners
			while( pendingTasks.any() && idleRunners.any() )
			{
				Task* task = 0;
				TaskRunner* runner = 0;
				pendingTasks.pop( task );
				if( task )
				{
					idleRunners.pop( runner );
					if( runner )
					{
						runner->setTask( task );
						activeRunners.push( runner );
						runner->start();
					}
				}
			}
		}

		void TaskManager::releaseRunnerFromTasks( TaskRunner* runner )
		{
			Task* task = runner->getTask();
			if( task && task->getState() != Task::Ended )
			{
				pendingTasks.push( task );
			}
			
			runner->setTask( 0 );
			runner->suspend();
			idleRunners.push( runner );
		}
	}
}