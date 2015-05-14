#pragma once

#include "NeutronFoundationCommon.h"

namespace Neutron
{
	namespace Concurrent
	{
		class NEUTRON_FOUNDATION_CORE SimpleLock
		{
			NEUTRON_LOCK lock;
			SimpleLock(const SimpleLock& other);
			SimpleLock& operator=(const SimpleLock& rhs);

		public:
			SimpleLock() { createLock(&lock); }
			virtual ~SimpleLock() { destroyLock(&lock); }

			inline void acquire() { acquireLock(&lock); }
			inline boolean tryAcquire() { return tryAcquireLock(&lock); }
			inline void release() { releaseLock(&lock); }
		};

		class NEUTRON_FOUNDATION_CORE SimpleEvent
		{
			NEUTRON_EVENT event;
			SimpleEvent(const SimpleEvent& other);
			SimpleEvent& operator=(const SimpleEvent& rhs);

		public:
			SimpleEvent(boolean manualReset, boolean initState) { event = createEvent(manualReset, initState); assert(event != 0); }
			virtual ~SimpleEvent() { destroyEvent(event); }

			void set() { setEvent(event); }
			void reset() { resetEvent(event); }
			void wait(uint32 time) { waitEvent(event, time); }
			inline NEUTRON_EVENT getHandle() const { return event; }
		};

		class NEUTRON_FOUNDATION_CORE ScopedLock
		{
			SimpleLock*	lockReference;
			ScopedLock(const ScopedLock& other);
			ScopedLock& operator=(const ScopedLock& rhs);

		public:
			ScopedLock(SimpleLock& lock) : lockReference(&lock) { lockReference->acquire(); }
			virtual ~ScopedLock() { lockReference->release(); }
		};

		class NEUTRON_FOUNDATION_CORE ReadWriteLock
		{
			SimpleLock counterLock;
			SimpleLock writeLock;
			volatile uint32 counter;
			ReadWriteLock(const ReadWriteLock& other);
			ReadWriteLock& operator=(const ReadWriteLock& rhs);

		public:
			ReadWriteLock();
			virtual ~ReadWriteLock();

			void lockRead();
			void unlockRead();
			void lockWrite();
			void unlockWrite();
		};

		class NEUTRON_FOUNDATION_CORE SimpleThread
		{
		public:
			typedef NEUTRON_THREAD_ENTRY ThreadFunc;
			static const int WAIT_TIME_INFINITE = NEUTRON_WAIT_TIME_INFINITE;

		private:
			NEUTRON_THREAD_ID			id;
			NEUTRON_THREAD_HANDLE		handle;
			boolean						running;

			SimpleThread(const SimpleThread& other);
			SimpleThread& operator=(const SimpleThread& rhs);

		public:
			SimpleThread();
			virtual ~SimpleThread();

			boolean init(ThreadFunc func, void* arg);
			void release();

			void start();
			void suspend();
			void wait(int time = WAIT_TIME_INFINITE);

			inline NEUTRON_THREAD_ID getId() const { return id; }
			inline NEUTRON_THREAD_HANDLE getHandle() const { return handle; }
			inline boolean isRunning() const { return running; }
		};
	}
}