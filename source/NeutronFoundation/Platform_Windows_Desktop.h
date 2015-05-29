#pragma once

#ifdef _WIN32

// platform symbol
#define VRLAB_WINDOWS
#define VRLAB_WINDOWS_DESKTOP

#if defined _M_AMD64
#define VRLAB_BUILD_ARCH_AMD64
#elif defined _M_IX86
#define VRLAB_BUILD_ARCH_IX86
#elif defined _M_IA64
#define VRLAB_BUILD_ARCH_IA64
#elif defined _M_X64
#define VRLAB_BUILD_ARCH_X64
#endif

#if defined _WIN64
#define VRLAB_BUILD_X64
#else
#define VRLAB_BUILD_X86
#endif

#ifdef _DEBUG
#define VRLAB_DEBUG
#endif

#pragma warning( disable: 4251 )
#pragma warning( disable: 4996 )

#include <WinSock2.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <process.h>

#include <cassert>
#include <deque>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <math.h>
#include <functional>

namespace VRLab
{
		// language
#define VRLAB_FORCE_INLINE __forceinline

	typedef bool boolean;
	typedef wchar_t wchar;
	typedef char int8;
	typedef short int16;
	typedef int int32;
	typedef __int64 int64;
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned __int64 uint64;

#if defined VRLAB_BUILD_X86
	typedef unsigned int uintptr;
	typedef unsigned int Size;
#elif defined VRLAB_BUILD_X64
	typedef unsigned __int64 uintptr;
	typedef unsigned __int64 Size;
#endif

#define VRLAB_FLT_MIN		FLT_MIN
#define VRLAB_FLT_MAX		FLT_MAX
#define VRLAB_DBL_MIN		DBL_MIN
#define VRLAB_DBL_MAX		DBL_MAX

	// memory
	inline void* alloc( Size s ) { return ::malloc( s ); }
	inline void* realloc( void* p, Size s ) { return ::realloc( p, s ); }
	inline void free( void* p ) { return ::free( p ); }

	// plugin
#define VRLAB_PROCESS_INSTANCE HINSTANCE
#define VRLAB_PLUGIN_HANDLE HMODULE
#define VRLAB_PLUGIN_EXPORT __declspec( dllexport )
#define VRLAB_PLUGIN_IMPORT __declspec( dllimport )
#define VRLAB_PLUGIN_SYMBOL_ADDRESS FARPROC

	inline VRLAB_PLUGIN_HANDLE loadPlugin( const char* path ) { return ::LoadLibraryA( path ); }
	inline void unloadPlugin( VRLAB_PLUGIN_HANDLE plugin ) { ::FreeLibrary( plugin ); }
	inline VRLAB_PLUGIN_SYMBOL_ADDRESS getPluginSymbol( VRLAB_PLUGIN_HANDLE plugin, const char* name ) { return ::GetProcAddress( plugin, name ); }

	// lock & event
#define VRLAB_LOCK CRITICAL_SECTION
#define VRLAB_EVENT HANDLE
#define VRLAB_WAIT_TIME_INFINITE INFINITE
	
	inline void createLock( VRLAB_LOCK* lock ) { return ::InitializeCriticalSection( lock ); }
	inline void acquireLock( VRLAB_LOCK* lock ) { return ::EnterCriticalSection( lock ); }
	inline boolean tryAcquireLock( VRLAB_LOCK* lock ) { return ::TryEnterCriticalSection( lock ) == TRUE; }
	inline void releaseLock( VRLAB_LOCK* lock ) { return ::LeaveCriticalSection( lock ); }
	inline void destroyLock( VRLAB_LOCK* lock ) { return ::DeleteCriticalSection( lock ); }
	inline VRLAB_EVENT createEvent( boolean manualReset, boolean initialState ) { return CreateEvent( 0, manualReset, initialState, 0 ); }
	inline void setEvent( VRLAB_EVENT e ) { ::SetEvent( e ); }
	inline void resetEvent( VRLAB_EVENT e ) { ::ResetEvent( e ); }
	inline void waitEvent( VRLAB_EVENT e, uint32 time ) { ::WaitForSingleObject( e, time ); }
	inline void waitEvents( VRLAB_EVENT* e, uint32 numEvents, boolean waitAll, uint32 time ) { ::WaitForMultipleObjects( numEvents, e, waitAll, time ); }
	inline void destroyEvent( VRLAB_EVENT e ) { ::CloseHandle( e ); e = 0; }

	// atom operations
	inline boolean atomCAS16( volatile int16* x, int16 v1, int16 v0 ) { return InterlockedCompareExchange16( x, v1, v0 ) == v0; }
	inline boolean atomCAS32( volatile uint32* x, uint32 v1, uint32 v0 ) { return InterlockedCompareExchange( x, v1, v0 ) == v0; }
	inline boolean atomCAS64( volatile int64* x, int64 v1, int64 v0 ) { return InterlockedCompareExchange64( x, v1, v0 ) == v0; }
	inline void atomIncrement16( volatile int16* x ) { InterlockedIncrement16( x ); }
	inline void atomIncrement32( volatile int32* x ) { InterlockedIncrement( (long*)x ); }
	inline void atomIncrement64( volatile int64* x ) { InterlockedIncrement64( x ); }
	inline void atomDecrement16( volatile int16* x ) { InterlockedDecrement16( x ); }
	inline void atomDecrement32( volatile int32* x ) { InterlockedDecrement( (long*)x ); }
	inline void atomDecrement64( volatile int64* x ) { InterlockedDecrement64( x ); }

	// thread
	typedef uint32( __stdcall * _ThreadFunc )( void* );
#define VRLAB_THREAD_ENTRY _ThreadFunc
#define VRLAB_THREAD_HANDLE HANDLE
#define VRLAB_THREAD_ID uint32
#define VRLAB_THREAD_YIELD SwitchToThread

	inline VRLAB_THREAD_HANDLE initThread( VRLAB_THREAD_ENTRY entry, void* args, VRLAB_THREAD_ID* thread_id ) { return (VRLAB_THREAD_HANDLE)::_beginthreadex( 0, 0, entry, args, CREATE_SUSPENDED, thread_id ); }
	inline void resumeThread( VRLAB_THREAD_HANDLE t ) { ::ResumeThread( t ); }
	inline void suspendThread( VRLAB_THREAD_HANDLE t ) { ::SuspendThread( t ); }
	inline VRLAB_THREAD_ID getCurrentThreadID() { return ::GetCurrentThreadId(); }
	inline void waitThread( VRLAB_THREAD_HANDLE t, uint32 time ) { ::WaitForSingleObject( t, time ); }
	inline void waitThreads( VRLAB_THREAD_HANDLE* t, uint32 numThreads, boolean waitAll, uint32 time ) { ::WaitForMultipleObjects( numThreads, t, waitAll, time ); }
	inline void closeThread( VRLAB_THREAD_HANDLE t ) { ::CloseHandle( t ); }
	inline void sleep( uint32 time ) { ::Sleep( time ); }
	inline void yield() { ::SwitchToThread(); }
	
	// network
#define VRLAB_INVALID_FD INVALID_SOCKET
	inline void networkStartup() { WSADATA data; WSAStartup( MAKEWORD( 2, 2 ), &data ); }
	inline void networkShutdown() { WSACleanup(); }

	// guid
	struct Guid
	{
		uint32 data1;
		uint32 data2;
		uint32 data3;
		uint32 data4;
	};

	inline Guid generateGuid()
	{
		GUID native;
		CoCreateGuid( &native );
		Guid ret;
		ret.data1 = native.Data1;
		ret.data2 = *reinterpret_cast<uint32*>( &native.Data2 );
		ret.data3 = *reinterpret_cast<uint32*>( &native.Data4 );
		ret.data4 = *reinterpret_cast<uint32*>( &native.Data4[4] );
		return ret;
	}
}

#endif