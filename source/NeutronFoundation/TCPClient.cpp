#pragma once

#include "TCPClient.h"

namespace Neutron
{
	namespace Network
	{
		// TCPClientUpdateTask
		TCPClientReceivingTask::TCPClientReceivingTask( TCPClient* owner )
			:owner( owner )
		{
			assert( this->owner );
		}

		TCPClientReceivingTask::~TCPClientReceivingTask()
		{
		}

		TaskPtr TCPClientReceivingTask::create( TCPClient* owner )
		{
			return TaskPtr( new TCPClientReceivingTask( owner ) );
		}

		void TCPClientReceivingTask::onStart()
		{
			setUpdateFlag( true );
		}

		void TCPClientReceivingTask::onUpdate()
		{
			if( !owner->getExitFlag() )
			{
				owner->receivingThread();
			}
			else
			{
				stop();
			}
		}

		void TCPClientReceivingTask::onStop()
		{
		}

		void TCPClientReceivingTask::onAbort()
		{
		}

		// TCPClient
		TCPClient::TCPClient()
			: taskManager( 0 )
			, recvBufferSize( 0 )
		{
		}

		TCPClient::~TCPClient()
		{
		}

		boolean TCPClient::init( TaskManager* taskManager, const char* address, int port, Size recvBufferSize )
		{
			if( !taskManager || !address || address[0] == '\0' || port == 0 || recvBufferSize == 0 )
			{
				return false;
			}

			this->taskManager = taskManager;
			if( !socket.connect( address, port ) )
			{
				return false;
			}

			this->taskManager = taskManager;
			this->recvBufferSize = recvBufferSize;

			recvBuffer = new uint8[recvBufferSize];
			assert( recvBuffer );

			receivingTask = TCPClientReceivingTask::create( this );
			taskManager->assign( receivingTask );

			exitFlag = false;

			return true;
		}

		void TCPClient::release()
		{
			// set exit flag
			exitFlag = true;

			// wait tasks ended
			while( receivingTask->getState() != Task::Ended );

			if( recvBuffer )
			{
				delete [] recvBuffer;
				recvBuffer = 0;
			}

			taskManager = 0;
			recvBufferSize = 0;

			// close socket
			socket.disconnect();
		}

		boolean TCPClient::isConnected()
		{
			return socket.isConnected();
		}

		Size TCPClient::send( uint8* buffer, Size size )
		{
			Size sentSize = 0;
			int retCode = socket.send( buffer, size, &sentSize );
			if( retCode == SOCKET_RETURN_LOST_CONNECTION || retCode == SOCKET_RETURN_ERROR_UNKNOWN )
			{
				onLostConnection();
			}
			return sentSize;
		}

		void TCPClient::receivingThread()
		{
			Size receivedSize = 0;
			int retCode = socket.recv( recvBuffer, recvBufferSize, &receivedSize );
			if( retCode == SOCKET_RETURN_REMOTE_CLOSED )
			{
				onDisconnected();
			}
			else if( retCode == SOCKET_RETURN_LOST_CONNECTION || retCode == SOCKET_RETURN_ERROR_UNKNOWN )
			{
				onLostConnection();
			}
			else if( retCode == SOCKET_RETURN_OK )
			{
				onReceive( recvBuffer, receivedSize );
			}
		}

		void TCPClient::onDisconnected()
		{
			printf( "server disconnected\n" );
		}

		void TCPClient::onLostConnection()
		{
			printf( "lost connection with server\n" );
		}

		void TCPClient::onReceive( uint8* buffer, Size size )
		{
			printf( "received from server size = %u\n", size);
			printf( "content = %s\n", buffer );
		}
	}
}