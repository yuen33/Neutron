#include "Thread.h"

namespace Neutron
{
	namespace Concurrent
	{
		// ReadWriteLock
		ReadWriteLock::ReadWriteLock()
		{
		}

		ReadWriteLock::~ReadWriteLock()
		{
			assert( counter == 0 );
		}

		void ReadWriteLock::lockRead()
		{
			ScopedLock lock( counterLock );
			++counter;
			if( counter > 0 )
			{
				writeLock.acquire();
			}
		}

		void ReadWriteLock::unlockRead()
		{
			ScopedLock lock( counterLock );
			--counter;
			if( counter == 0 )
			{
				writeLock.release();
			}
		}

		void ReadWriteLock::lockWrite()
		{
			writeLock.acquire();
		}

		void ReadWriteLock::unlockWrite()
		{
			writeLock.release();
		}

		// SimpleThread
		SimpleThread::SimpleThread()
			:id( 0 )
			, handle( 0 )
		{
		}

		SimpleThread::~SimpleThread()
		{
		}

		boolean SimpleThread::init( ThreadFunc func, void* args )
		{
			handle = initThread( func, args, &id );
			assert( handle );
			return handle != 0;
		}

		void SimpleThread::release()
		{
			if( handle != 0 )
			{
				wait();
				closeThread( handle );
				handle = 0;
			}
		}

		void SimpleThread::start()
		{
			resumeThread( handle );
		}

		void SimpleThread::suspend()
		{
			suspendThread( handle );
		}

		void SimpleThread::wait( int time )
		{
			assert( handle );
			if( getCurrentThreadID() != id )
			{
				waitThread( handle, time );
			}
		}
	}
}