#include "TCPServer.h"
#include "Array.h"
using Neutron::Container::Array;

namespace Neutron
{
	namespace Network
	{
		// TCPServerListenTask
		TCPServerListeningTask::TCPServerListeningTask( TCPServer* owner )
			:owner( owner )
		{
			assert( this->owner );
		}

		TCPServerListeningTask::~TCPServerListeningTask()
		{
		}

		TaskPtr TCPServerListeningTask::create( TCPServer* owner )
		{
			return TaskPtr( new TCPServerListeningTask( owner ) );
		}

		void TCPServerListeningTask::onStart()
		{
			setUpdateFlag( true );
		}

		void TCPServerListeningTask::onUpdate()
		{
			if( !owner->getExitFlag() )
			{
				owner->listeningThread();
			}
			else
			{
				stop();
			}
		}

		void TCPServerListeningTask::onStop()
		{
		}

		void TCPServerListeningTask::onAbort()
		{
		}

		// TCPServerUpdateTask
		TCPServerReceivingTask::TCPServerReceivingTask( TCPServer* owner )
			: owner( owner )
		{
			assert( this->owner );
		}

		TCPServerReceivingTask::~TCPServerReceivingTask()
		{
		}

		TaskPtr TCPServerReceivingTask::create( TCPServer* owner )
		{
			return TaskPtr( new TCPServerReceivingTask( owner ) );
		}

		void TCPServerReceivingTask::onStart()
		{
			setUpdateFlag( true );
		}

		void TCPServerReceivingTask::onUpdate()
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

		void TCPServerReceivingTask::onStop()
		{
		}

		void TCPServerReceivingTask::onAbort()
		{
		}

		// TCPServer
		TCPServer::TCPServer()
			: taskManager( 0 )
			, recvBufferSize( 0 )
			, recvBuffer( 0 )
			, exitFlag( false )
		{
		}

		TCPServer::~TCPServer()
		{
		}

		boolean TCPServer::init( TaskManager* taskManager, const char* address, int port, Size recvBufferSize )
		{
			if( !taskManager || !address || address[0] == '\0' || port == 0 || recvBufferSize == 0)
			{
				return false;
			}

			this->taskManager = taskManager;
			if( !listenSocket.init( address, port ) )
			{
				return false;
			}

			this->taskManager = taskManager;
			this->recvBufferSize = recvBufferSize;

			recvBuffer = new uint8[recvBufferSize];
			assert( recvBuffer );

			listenTask = TCPServerListeningTask::create( this );
			updateTask = TCPServerReceivingTask::create( this );
			taskManager->assign( updateTask );
			taskManager->assign( listenTask );

			exitFlag = false;

			return true;
		}

		void TCPServer::release()
		{
			// set exit flag
			exitFlag = true;

			// wait tasks ended
			while( listenTask->getState() != Task::Ended || updateTask->getState() != Task::Ended );

			if( recvBuffer )
			{
				delete [] recvBuffer;
				recvBuffer = 0;
			}

			taskManager = 0;
			recvBufferSize = 0;

			// close listen socket
			listenSocket.release();

			// close all session sockets
			sessionsLock.acquire();
			for( HashMap<uint32, TCPSessionSocket*>::Iterator it = sessionSockets.begin(); it != sessionSockets.end(); ++it )
			{
				TCPSessionSocket* sessionSocket = it.value();
				sessionSocket->release();
				delete sessionSocket;
			}
			sessionSockets.clear();
			sessionsLock.release();
		}

		void TCPServer::update()
		{
			/*sessionsLock.acquire();
			for( HashMap<uint32, TCPSessionSocket*>::Iterator it = sessionSockets.begin(); it != sessionSockets.end(); ++it )
			{
				TCPSessionSocket* sessionSocket = it.value();
				if( !sessionSocket->isConnected() )
				{
					sessionSocket->release();
					delete sessionSocket;
				}
			}
			sessionsLock.release();*/
		}

		boolean TCPServer::isConnected( const char* address, int port )
		{
			TCPSessionSocket* sessionSocket = getSessionSocket( address, port );
			return sessionSocket && sessionSocket->isConnected();
		}

		TCPSessionSocket* TCPServer::getSessionSocket( const char* address, int port )
		{
			uint32 key = NetAddress::getHashValue( address, port );

			sessionsLock.acquire();
			HashMap<uint32, TCPSessionSocket*>::Iterator it = sessionSockets.find( key );
			sessionsLock.release();

			if( it != sessionSockets.end() )
			{
				return it.value();
			}
			return 0;
		}

		Size TCPServer::sendTo( const char* address, int port, uint8* buffer, Size size )
		{
			TCPSessionSocket* sessionSocket = getSessionSocket( address, port );
			if( sessionSocket && sessionSocket->isConnected() )
			{
				Size sentSize = 0;
				int retCode = sessionSocket->send( buffer, size, &sentSize );
				if( retCode == SOCKET_RETURN_LOST_CONNECTION || retCode == SOCKET_RETURN_ERROR_UNKNOWN || retCode == SOCKET_RETURN_REMOTE_CLOSED )
				{
					sessionSockets.remove( NetAddress::getHashValue( address, port ) );

					sessionsLock.acquire();
					onLostConnectionTo( sessionSocket->getNetAddress().getAddress(), sessionSocket->getNetAddress().getPort() );
					sessionsLock.release();

					sessionSocket->release();
					delete sessionSocket;
				}
				return sentSize;
			}

			return 0;
		}

		void TCPServer::broadcast( uint8* buffer, Size size )
		{
			sessionsLock.acquire();
			Array<uint32> removeList;
			for( HashMap<uint32, TCPSessionSocket*>::Iterator it = sessionSockets.begin(); it != sessionSockets.end(); ++it )
			{
				TCPSessionSocket* sessionSocket = it.value();
				if( sessionSocket->isConnected() )
				{
					Size sentSize = 0;
					int retCode = sessionSocket->send( buffer, size, &sentSize );
					if( retCode == SOCKET_RETURN_LOST_CONNECTION || retCode == SOCKET_RETURN_ERROR_UNKNOWN || retCode == SOCKET_RETURN_REMOTE_CLOSED )
					{
						removeList.add( it.key() );
						onLostConnectionTo( sessionSocket->getNetAddress().getAddress(), sessionSocket->getNetAddress().getPort() );
						sessionSocket->release();
						delete sessionSocket;
					}
				}
			}

			for( int i = 0; i < removeList.getCount(); ++i )
			{
				sessionSockets.remove( removeList[i] );
			}
			sessionsLock.release();
		}

		void TCPServer::listeningThread()
		{
			listenSocket.listen();
			SocketData remoteSocketData;
			if( listenSocket.accept( remoteSocketData, 16 ) )
			{
				TCPSessionSocket* sessionSocket = new TCPSessionSocket();
				if( !sessionSocket->init( remoteSocketData ) )
				{
					delete sessionSocket;
					return;
				}

				sessionsLock.acquire();
				sessionSockets.add( sessionSocket->getNetAddress().getHashValue(), sessionSocket );
				sessionsLock.release();

				onConnectedTo( sessionSocket->getNetAddress().getAddress(), sessionSocket->getNetAddress().getPort() );
			}
		}

		void TCPServer::receivingThread()
		{
			sessionsLock.acquire();
			Array<uint32> removeList;
			for( HashMap<uint32, TCPSessionSocket*>::Iterator it = sessionSockets.begin(); it != sessionSockets.end(); ++it )
			{
				TCPSessionSocket* sessionSocket = it.value();
				memset( recvBuffer, 0, sizeof( recvBufferSize ) );

				Size recvSize = 0;
				int ret = sessionSocket->recv( recvBuffer, recvBufferSize, &recvSize );
				if( ret == SOCKET_RETURN_REMOTE_CLOSED )
				{
					removeList.add( it.key() );
					onDisconnectedFrom( sessionSocket->getNetAddress().getAddress(), sessionSocket->getNetAddress().getPort() );
					sessionSocket->release();
					delete sessionSocket;
				}
				else if( ret == SOCKET_RETURN_LOST_CONNECTION || ret == SOCKET_RETURN_ERROR_UNKNOWN )
				{
					removeList.add( it.key() );
					onLostConnectionTo( sessionSocket->getNetAddress().getAddress(), sessionSocket->getNetAddress().getPort() );
					sessionSocket->release();
					delete sessionSocket;
				}
				else if( ret == SOCKET_RETURN_OK )
				{
					onRecvFrom( sessionSocket->getNetAddress().getAddress(), sessionSocket->getNetAddress().getPort(), recvBuffer, recvSize );
				}
			}

			for( int i = 0; i < removeList.getCount(); ++i )
			{
				sessionSockets.remove( removeList[i] );
			}

			sessionsLock.release();
		}

		void TCPServer::onConnectedTo( const char* address, int port )
		{
			printf( "%s:%d connected\n", address, port );
		}

		void TCPServer::onDisconnectedFrom( const char* address, int port )
		{
			printf( "%s:%d disconnected\n", address, port );
		}

		void TCPServer::onLostConnectionTo( const char* address, int port )
		{
			printf( "%s:%d lost connection\n", address, port );
		}

		void TCPServer::onRecvFrom( const char* address, int port, uint8* buffer, Size size )
		{
			printf( "received from %s:%d size = %u\n", address, port, size );
			printf( "content = %s\n", buffer );
		}
	}
}