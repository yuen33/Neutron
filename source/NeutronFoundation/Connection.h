#pragma once

#include "Socket.h"

namespace Neutron
{
	namespace Network
	{
		class Connection
		{
			int socketType;
			boolean server;

			union
			{
				TCPSessionSocket* tcpSessionSocket;
				TCPClientSocket* tcpClientSocket;
				UDPSocket* udpSocket;
			}socket;

		public:
			Connection();
			virtual ~Connection();

			boolean init( const SocketData& socketData );
			boolean init( const char* remoteAddress, int port );
			boolean init( int port );
			void release();

			int send( uint8* buffer, Size size, Size* sentSize = 0 );
			int recv( uint8* buffer, Size size, Size* receivedSize = 0, int waitTime = -1 );
			int sendTo( const char* address, int port, uint8* buffer, Size size, Size* sentSize = 0 );
			int recvFrom( uint8* buffer, Size size, NetAddress* remoteAddress, Size* receivedSize = 0, int waitTime = -1 );

			inline int getSocketType() const { return socketType; }
			inline boolean isServer() const { return server; }
			inline boolean valid() const { return socketType != SOCKET_TYPE_UNKNOWN; }
			inline TCPSessionSocket* getTCPSessionSocket() const { return socketType == SOCKET_TYPE_STREAM && server ? socket.tcpSessionSocket : 0; }
			inline TCPClientSocket* getTCPClientSocket() const { return socketType == SOCKET_TYPE_STREAM && !server ? socket.tcpClientSocket : 0; }
			inline UDPSocket* getUDPSocket() const { return socketType == SOCKET_TYPE_DGRAM ? socket.udpSocket : 0; }
		};
	}
}