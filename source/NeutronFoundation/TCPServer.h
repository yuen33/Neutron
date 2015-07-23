#pragma once

#include "NeutronFoundationCommon.h"
#include "Thread.h"
#include "TaskManager.h"
#include "Socket.h"
#include "HashMap.h"

using Neutron::Concurrent::SimpleLock;
using Neutron::Concurrent::Task;
using Neutron::Concurrent::TaskPtr;
using Neutron::Concurrent::TaskManager;
using Neutron::Container::HashMap;

namespace Neutron
{
	namespace Network
	{
		class TCPServer;

		class TCPServerListeningTask : public Task
		{
			TCPServer* owner;

			TCPServerListeningTask( TCPServer* owner );

		public:
			virtual ~TCPServerListeningTask();
			static TaskPtr create( TCPServer* owner );

			virtual void onStart();
			virtual void onUpdate();
			virtual void onStop();
			virtual void onAbort();
		};

		class TCPServerReceivingTask : public Task
		{
			TCPServer* owner;
			TCPServerReceivingTask( TCPServer* owner );

		public:
			virtual ~TCPServerReceivingTask();
			static TaskPtr create( TCPServer* owner );

			virtual void onStart();
			virtual void onUpdate();
			virtual void onStop();
			virtual void onAbort();
		};

		class NEUTRON_FOUNDATION_CORE TCPServer
		{
			TaskManager*						taskManager;
			TaskPtr								listenTask;
			TaskPtr								updateTask;
			TCPServerSocket						listenSocket;
			HashMap<uint32, TCPSessionSocket*>	sessionSockets;
			SimpleLock							sessionsLock;
			Size								recvBufferSize;
			boolean								exitFlag;
			uint8*								recvBuffer;

			TCPSessionSocket* getSessionSocket( const char* address, int port );
			void removeSessionSocket( uint32 key );

		public:
			TCPServer();
			virtual ~TCPServer();

			boolean init( TaskManager* taskManager, const char* address, int port, Size recvBufferSize );
			void release();
			void update();

			boolean isConnected( const char* address, int port );
			Size sendTo( const char* address, int port, uint8* buffer, Size size );
			void broadcast( uint8* buffer, Size size );

			void listeningThread();
			void receivingThread();

			virtual void onConnectedTo( const char* address, int port );
			virtual void onDisconnectedFrom( const char* address, int port );
			virtual void onLostConnectionTo( const char* address, int port );
			virtual void onRecvFrom( const char* address, int port, uint8* buffer, Size size );

			boolean getExitFlag() const { return exitFlag; }
		};
	}
}