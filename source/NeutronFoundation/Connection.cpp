#pragma once

#include "Connection.h"

namespace Neutron
{
	namespace Network
	{
		Connection::Connection()
			:socketType( SOCKET_TYPE_UNKNOWN )
			,server( false )
		{
		}

		Connection::~Connection()
		{
		}

		boolean Connection::init( const SocketData& socketData )
		{
			if( valid() )
			{
				release();
			}

			socket.tcpSessionSocket = new TCPSessionSocket();
			assert( socket.tcpSessionSocket );
			boolean ret = socket.tcpSessionSocket->init( socketData );
			if( ret )
			{
				socketType = SOCKET_TYPE_STREAM;
				server = true;
			}

			return ret;
		}

		boolean Connection::init( const char* remoteAddress, int port )
		{
			if( valid() )
			{
				release();
			}

			socket.tcpClientSocket = new TCPClientSocket();
			assert( socket.tcpClientSocket );
			boolean ret = socket.tcpClientSocket->connect( remoteAddress, port );
			if( ret )
			{
				socketType = SOCKET_TYPE_STREAM;
				server = false;
			}

			return ret;
		}

		boolean Connection::init( int port )
		{
			if( valid() )
			{
				release();
			}

			socket.udpSocket = new UDPSocket();
			assert( socket.udpSocket );
			boolean ret = socket.udpSocket->init( 0, port );
			if( ret )
			{
				socketType = SOCKET_TYPE_DGRAM;
				server = false;
			}

			return ret;
		}

		void Connection::release()
		{
			if( socketType == SOCKET_TYPE_STREAM )
			{
				if( server )
				{
					if( socket.tcpSessionSocket )
					{
						socket.tcpSessionSocket->release();
						delete socket.tcpSessionSocket;
						socket.tcpSessionSocket = 0;
					}
				}
				else
				{
					if( socket.tcpClientSocket )
					{
						socket.tcpClientSocket->disconnect();
						delete socket.tcpClientSocket;
						socket.tcpClientSocket = 0;
					}
				}
			}
			else if( socketType = SOCKET_TYPE_DGRAM )
			{
				if( socket.udpSocket )
				{
					socket.udpSocket->release();
					delete socket.udpSocket;
					socket.udpSocket = 0;
				}
			}

			server = false;
			socketType = SOCKET_TYPE_UNKNOWN;
		}

		int Connection::send( uint8* buffer, Size size, Size* sentSize )
		{
			if( socketType == SOCKET_TYPE_STREAM )
			{
				if( server )
				{
					return socket.tcpSessionSocket->send( buffer, size, sentSize );
				}
				else
				{
					return socket.tcpClientSocket->send( buffer, size, sentSize );
				}
			}

			return SOCKET_RETURN_ERROR_UNKNOWN;
		}

		int Connection::recv( uint8* buffer, Size size, Size* receivedSize, int waitTime )
		{
			if( socketType == SOCKET_TYPE_STREAM )
			{
				if( server )
				{
					return socket.tcpSessionSocket->recv( buffer, size, receivedSize, waitTime );
				}
				else
				{
					return socket.tcpClientSocket->recv( buffer, size, receivedSize, waitTime );
				}
			}

			return SOCKET_RETURN_ERROR_UNKNOWN;
		}

		int Connection::sendTo( const char* address, int port, uint8* buffer, Size size, Size* sentSize )
		{
			if( socketType == SOCKET_TYPE_DGRAM )
			{
				return socket.udpSocket->send( address, port, buffer, size, sentSize );
			}

			return SOCKET_RETURN_ERROR_UNKNOWN;
		}

		int Connection::recvFrom( uint8* buffer, Size size, NetAddress* remoteAddress, Size* recvSize, int waitTime )
		{
			if( socketType == SOCKET_TYPE_DGRAM )
			{
				return socket.udpSocket->recv( buffer, size, remoteAddress, recvSize, waitTime );
			}

			return SOCKET_RETURN_ERROR_UNKNOWN;
		}
	}
}