#pragma once

/*****************************************************************************************************************************
* Task Manager Usage:
* 1.	Each runner is simply a thread
* 2.	RunnerCount shoud greater than actual GPU core count but not recommand greater than 32,
*			because many small and quick tasks will lock runners when assign task and release task,
*			recommand to use multiple TaskManagers to handle different kind of tasks
* 3.	Be sure taskCapacity is greater than the max assigned tasks number in task manager or there will be assert
* 4.	Be sure onAbort() released all the resources, so this thread can be shutdown gracefully,
*			onAbort() will be called instead of onStop() when the task is shutdown not by itself
* 5.	Construct a simple task like this ( onUpdate() will not be called ):
*			class MyTask : public Task
*			{
*				boolean exitFlag;
*				public:
*				MyTask() {}
*				virtual ~MyTask() {}
*				virtual void onStart()
*				{
*					// work start
*				}
*				virtual void onStop()
*				{
*					// work stop
*				}
*			};
* 6.	Contruct task which will update peroidly like this ( not update by the same thread ):
*			class MyTask : public Task
*			{
*				boolean exitFlag;
*				public:
*				MyTask() : exitFlag( false ) { setUpdateFlag( true ); };
*				virtual ~MyTask() {}
*				virtual void onStart()
*				{
*					// work start
*				}
*				virtual void onUpdate()
*				{
*					// do update and using exitFlag as an exit trigger
*					if( exitFlag )
*					{
*						stop();		// this will stop task from updating
*					}
*				}
*				virtual void onStop()
*				{
*					// work stop
*				}
*			};
* 7.	Construct task whick will hold thread like this ( not released until finished ):
*			class MyTask : public Task
*			{
*				boolean exitFlag;
*				public:
*				MyTask() : exitFlag( false ) {};
*				virtual ~MyTask() {}
*				virtual void onStart()
*				{
*					// work start
*				}
*				virtual void onUpdate()
*				{
*					while( !exitFlag )
*					{
*						// do update and using exitFlag as an exit trigger
*					}
*				}
*				virtual void onStop()
*				{
*					// work stop
*				}
*			};
******************************************************************************************************************************/

#include "VRLabCommon.h"
#include "AsyncQueue.h"
#include <vector>
#include "Thread.h"
#include "Timer.h"
#include "RCPtr.h"

using std::vector;
using VRLab::Container::AsyncQueue;
using VRLab::Concurrent::SimpleEvent;
using VRLab::Concurrent::SimpleThread;
using VRLab::Utility::Timer;
using VRLab::Utility::RCObject;
using VRLab::Utility::RCPtr;

namespace VRLab
{
	namespace Concurrent
	{
		class Task;
		class TaskManager;
		typedef RCPtr<Task> TaskPtr;

		class VRLAB_CORE TaskRunner : public SimpleThread
		{
			TaskManager* owner;
			TaskPtr task;

		public:
			TaskRunner( TaskManager* owner );
			virtual ~TaskRunner();

			boolean init();
			void release();

			static uint32 __stdcall process( void* args );

			inline void setTask( TaskPtr newTask ) { task = newTask; }
			inline TaskPtr getTask() { return task; }
		};

		class VRLAB_CORE Task : public RCObject
		{
		public:
			enum : int
			{
				Initialized,
				Pending,
				Running,
				Ending,
				Ended,
			};

		private:
			int state;
			TaskRunner* runner;
			boolean updateFlag;
			boolean abortFlag;

		public:
			Task();
			virtual ~Task();

			// called once when task start
			virtual void onStart();
			// called when task update
			virtual void onUpdate();
			// called once when task finished
			virtual void onStop();
			// abort task, make sure the task will abort gracefully
			virtual void onAbort();

			inline void setRunner( TaskRunner* newRunner ) { runner = newRunner; }
			inline int getRunnerID() const { return runner->getID(); }
			inline void setState( int value ) { state = value; }
			inline int getState() const { return state; }
			inline void setUpdateFlag( boolean value ) { updateFlag = value; }
			inline boolean getUpdateFlag() const { return updateFlag; }
			inline boolean getAbortFlag() const { return abortFlag; }

			// refresh task for reassignment
			inline void refresh( boolean isUpdate ) { updateFlag = isUpdate; state = Task::Initialized; abortFlag = false; }
			// used in update() to exit
			inline void stop() { updateFlag = false; }
			// abort task, called when task manager release
			inline void abort() { abortFlag = true; }
		};

		class VRLAB_CORE TaskManager
		{
			vector<TaskRunner*>		runners;
			AsyncQueue<TaskPtr>		pendingTasks;

			SimpleEvent				pendingTaskEvent;
			SimpleEvent				exitEvent;
			boolean					exitFlag;
			volatile int			assignedTasks;
			volatile int			finishedTasks;

			// profiler timer
			//Timer					timer;

		public:
			TaskManager();
			virtual ~TaskManager();

			boolean init( int runnerCount, int taskCapacity );
			void release();

			boolean assign( TaskPtr task );
			void cancel( TaskPtr task );

			// task runner called
			void waitForTask();
			void assignRunnersToTasks( TaskRunner* runner );
			void releaseRunnerFromTasks( TaskRunner* runner );

			inline boolean getExitFlag() const { return exitFlag; }
			inline boolean isIdle() const { return assignedTasks == finishedTasks; }
			inline int getAssignedTasksCount() const { return assignedTasks; }
			inline int getFinishedTasksCount() const { return finishedTasks; }
		};
	}
}