#pragma once

#include "NeutronFoundationCommon.h"
#include "AsyncQueue.h"
#include "Thread.h"

using Neutron::Container::AsyncQueue;
using Neutron::Concurrent::SimpleThread;

namespace Neutron
{
	namespace Utility
	{
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
			boolean suspendFlag;
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

			inline void setState( int value ) { state = value; }
			inline int getState() const { return state; }
			inline void setUpdateFlag( boolean value ) { updateFlag = value; }
			inline boolean getUpdateFlag() const { return updateFlag; }
			inline boolean getAbortFlag() const { return abortFlag; }

			// used in update() to exit
			inline void stop() { updateFlag = false; }
			// pause task
			inline void suspend() { suspendFlag = true; }
			// resume task
			inline void resume() { suspendFlag = false; }
			// abort task, called when task manager release
			inline void abort() { abortFlag = true; }
		};

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

			inline boolean setTask( Task* newTask ) { task = newTask; }
			inline Task* getTask() { return task; }
		};

		class NEUTRON_FOUNDATION_CORE TaskManager
		{
			AsyncQueue<TaskRunner*> idleRunners;
			AsyncQueue<TaskRunner*> activeRunners;
			AsyncQueue<Task*> pendingTasks;
			AsyncQueue<Task*> runningTasks;

			boolean flushFlag;
			boolean exitFlag;

		public:
			TaskManager();
			virtual ~TaskManager();

			boolean init( int runnerCount, int taskCapacity );
			void release();

			boolean assign( Task* task );
			void flush();

			void update();
			void assignRunnersToTasks();
			void releaseRunnerFromTasks( TaskRunner* runner );			
		};
	}
}