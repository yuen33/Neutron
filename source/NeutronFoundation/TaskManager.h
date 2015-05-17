#pragma once

#include "NeutronFoundationCommon.h"
#include "AsyncQueue.h"
#include "Array.h"
#include "Thread.h"
#include "Timer.h"

using Neutron::Container::Array;
using Neutron::Container::AsyncQueue;
using Neutron::Concurrent::SimpleEvent;
using Neutron::Concurrent::SimpleThread;

namespace Neutron
{
	namespace Utility
	{
		class Task;
		class TaskManager;
		
		class NEUTRON_FOUNDATION_CORE TaskRunner : public SimpleThread
		{
			TaskManager* owner;
			Task* task;

		public:
			TaskRunner( TaskManager* owner );
			virtual ~TaskRunner();

			boolean init();
			void release();

			static uint32 __stdcall process( void* args );

			inline void setTask( Task* newTask ) { task = newTask; }
			inline Task* getTask() { return task; }
		};

		class NEUTRON_FOUNDATION_CORE Task
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
			virtual void onStart();
			// called when the task get a owner
			virtual void onUpdate();
			// called onece when the task finished
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

			// used in update() to exit
			inline void stop() { updateFlag = false; }
			// abort task, called when task manager release
			inline void abort() { abortFlag = true; }
		};

		class NEUTRON_FOUNDATION_CORE TaskManager
		{
			Array<TaskRunner*>		runners;
			AsyncQueue<Task*>		pendingTasks;

			SimpleEvent				pendingTaskEvent;
			SimpleEvent				exitEvent;
			boolean					exitFlag;
			volatile int			assignedTasks;
			volatile int			finishedTasks;

			Timer					timer;

		public:
			TaskManager();
			virtual ~TaskManager();

			boolean init( int runnerCount, int taskCapacity );
			void release();

			boolean assign( Task* task );
			void cancel( Task* task );

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