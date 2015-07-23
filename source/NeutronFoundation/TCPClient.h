#pragma once

#include "NeutronFoundationCommon.h"
#include "Socket.h"
#include "TaskManager.h"

using Neutron::Concurrent::Task;
using Neutron::Concurrent::TaskPtr;
using Neutron::Concurrent::TaskManager;

namespace Neutron
{
	namespace Network
	{
		class TCPClient;

		class TCPClientReceivingTask : public Task
		{
			TCPClient* owner;

			TCPClientReceivingTask( TCPClient* owner );

		public:
			virtual ~TCPClientReceivingTask();
			static TaskPtr create( TCPClient* owner );

			virtual void onStart();
			virtual void onUpdate();
			virtual void onStop();
			virtual void onAbort();
		};

		class NEUTRON_FOUNDATION_CORE TCPClient
		{
			TaskManager*						taskManager;
			TaskPtr								receivingTask;
			TCPClientSocket						socket;
			Size								recvBufferSize;
			uint8*								recvBuffer;

			boolean exitFlag;

		public:
			TCPClient();
			virtual ~TCPClient();

			boolean init( TaskManager* taskManager, const char* address, int port, Size recvBufferSize );
			void release();
			void update();

			boolean isConnected();
			Size send( uint8* buffer, Size size );
			
			virtual void onDisconnected();
			virtual void onLostConnection();
			virtual void onReceive( uint8* buffer, Size size );

			void receivingThread();

			boolean getExitFlag() const { return exitFlag; }
		};
	}
}