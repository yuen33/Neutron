#include "Socket.h"

namespace Neutron
{
	namespace Network
	{
		// Network init
		boolean init()
		{
#ifdef NEUTRON_WINDOWS_DESKTOP
			WSAData wsa_data;
			return WSAStartup( MAKEWORD( 2, 2 ), &wsa_data ) == 0;
#endif
		}

		void release()
		{
#ifdef NEUTRON_WINDOWS_DESKTOP
			WSACleanup();
#endif
		}

		// UDP socket
		UDPSocket::UDPSocket()
			:block( true )
		{
			socketData.fd = NEUTRON_INVALID_FD;
		}

		UDPSocket::~UDPSocket()
		{
		}

		boolean UDPSocket::init( const char* address, int port, boolean blocking )
		{
			// create socket
			if( !address || address[0] == '\0' )
			{
				hostent* localHost = gethostbyname( "" );
				char* localIP = inet_ntoa( *( struct in_addr* )*localHost->h_addr_list );
				socketData.netAddress.setAddress( localIP );
			}
			else
			{
				socketData.netAddress.setAddress( address );
			}

			socketData.fd = NEUTRON_INVALID_FD;
			socketData.netAddress.setPort( port );
			socketData.socketType = SOCKET_TYPE_DGRAM;
			socketData.fd = socket( AF_INET, SOCK_DGRAM, 0 );
			if( socketData.fd == NEUTRON_INVALID_FD )
			{
				return false;
			}

			// set control parameter
			u_long nonBlocking = blocking ? 0 : 1;
			int ret = ioctlsocket( socketData.fd, FIONBIO, &nonBlocking );
			if( ret != 0 )
			{
				return false;
			}
			block = blocking;

			// bind
			sockaddr_in bindSocketAddr;
			bindSocketAddr.sin_family = AF_INET;
			bindSocketAddr.sin_addr.s_addr = socketData.netAddress.getINetAddress();
			bindSocketAddr.sin_port = socketData.netAddress.getINetPort();

			ret = ::bind( socketData.fd, (SOCKADDR*)&bindSocketAddr, sizeof( bindSocketAddr ) );
			if( ret != 0 )
			{
				release();
				return false;
			}
			//DWORD err = GetLastError();
			return ret == 0;
		}

		void UDPSocket::release()
		{
			if( socketData.fd != NEUTRON_INVALID_FD )
			{
				closesocket( socketData.fd );
				socketData.fd = NEUTRON_INVALID_FD;
			}
		}

		int UDPSocket::send( const char* remoteAddress, int port, uint8* buffer, Size size, Size* sentSize )
		{
			sockaddr_in connectSockAddr;
			connectSockAddr.sin_family = AF_INET;
			connectSockAddr.sin_addr.s_addr = inet_addr( remoteAddress );
			connectSockAddr.sin_port = htons( port );
			int ret = ::sendto( socketData.fd, (char*)buffer, (int)size, 0, (SOCKADDR*)&connectSockAddr, sizeof( connectSockAddr ) );

			int retError = SOCKET_RETURN_OK;
			if( ret < 0 )
			{
				int wsaError = WSAGetLastError();
				switch( wsaError )
				{
				case WSAEWOULDBLOCK:
					retError = SOCKET_RETURN_BLOCK; break;
				case WSAECONNRESET:
					retError = SOCKET_RETURN_LOST_CONNECTION; break;
				default:
					retError = SOCKET_RETURN_ERROR_UNKNOWN;
				}

				if( sentSize )
				{
					*sentSize = 0;
				}
			}
			else
			{
				if( sentSize )
				{
					*sentSize = ret;
				}

				retError = SOCKET_RETURN_OK;
			}

			return retError;
		}

		int UDPSocket::recv( uint8* buffer, Size size, NetAddress* remoteAddress, Size* receivedSize, int waitTime )
		{
			if( waitTime >= 0 )
			{
				fd_set reads;
				FD_ZERO( &reads );
				FD_SET( socketData.fd, &reads );
				timeval time;
				time.tv_sec = waitTime / 1000;
				time.tv_usec = waitTime % 1000;
				select( 0, &reads, 0, 0, &time );
				if( !FD_ISSET( socketData.fd, &reads ) )
				{
					return SOCKET_RETURN_NOTHING;
				}
			}

			sockaddr_in sockAddr;
			int sockAddrSize = sizeof( sockAddr );
			int ret = ::recvfrom( socketData.fd, (char*)buffer, (int)size, 0, (sockaddr*)&sockAddr, &sockAddrSize );

			int retError = SOCKET_RETURN_OK;
			if( ret <= 0 )
			{
				if( ret == 0 )
				{
					retError = SOCKET_RETURN_REMOTE_CLOSED;
				}
				else
				{
					int wsaError = WSAGetLastError();
					switch( wsaError )
					{
					case WSAEWOULDBLOCK:
						retError = SOCKET_RETURN_BLOCK; break;
					case WSAECONNRESET:
						retError = SOCKET_RETURN_LOST_CONNECTION; break;
					default:
						retError = SOCKET_RETURN_ERROR_UNKNOWN;
					}
				}

				if( remoteAddress )
				{
					remoteAddress->reset();
				}

				if( receivedSize )
				{
					*receivedSize = 0;
				}
			}
			else if( ret > 0 )
			{
				retError = SOCKET_RETURN_OK;
				if( remoteAddress )
				{
					remoteAddress->setINetAddress( sockAddr.sin_addr.s_addr );
					remoteAddress->setINetPort( sockAddr.sin_port );
				}

				if( receivedSize )
				{
					*receivedSize = ret;
				}
			}

			return retError;

		}

		// TCP server socket
		TCPServerSocket::TCPServerSocket()
			:block( true )
		{
			socketData.fd = NEUTRON_INVALID_FD;
		}

		TCPServerSocket::~TCPServerSocket()
		{
		}

		boolean TCPServerSocket::init( const char* address, int port, boolean blocking )
		{
			// create socket
			if( !address || address[0] == '\0' )
			{
				hostent* localHost = gethostbyname( "" );
				char* localIP = inet_ntoa( *( struct in_addr* )*localHost->h_addr_list );
				socketData.netAddress.setAddress( localIP );
			}
			else
			{
				socketData.netAddress.setAddress( address );
			}

			socketData.fd = NEUTRON_INVALID_FD;
			socketData.netAddress.setPort( port );
			socketData.socketType = SOCKET_TYPE_STREAM;
			socketData.fd = socket( AF_INET, SOCK_STREAM, 0 );
			if( socketData.fd == NEUTRON_INVALID_FD )
			{
				return false;
			}

			// set control parameter;
			u_long nonBlocking = blocking ? 0 : 1;
			int ret = ioctlsocket( socketData.fd, FIONBIO, &nonBlocking );
			if( ret != 0 )
			{
				release();
				return false;
			}
			block = blocking;

			// bind
			sockaddr_in bindSockAddr;
			bindSockAddr.sin_family = AF_INET;
			bindSockAddr.sin_addr.s_addr = socketData.netAddress.getINetAddress();
			bindSockAddr.sin_port = socketData.netAddress.getINetPort();

			ret = ::bind( socketData.fd, (SOCKADDR*)&bindSockAddr, sizeof( bindSockAddr ) );
			if( ret != 0 )
			{
				release();
				return false;
			}

			return ret == 0;
		}

		void TCPServerSocket::release()
		{
			if( socketData.fd != NEUTRON_INVALID_FD )
			{
				closesocket( socketData.fd );
				socketData.fd = NEUTRON_INVALID_FD;
			}
		}

		void TCPServerSocket::listen( int maxConnectionCount )
		{
			::listen( socketData.fd, maxConnectionCount > 0 ? maxConnectionCount : SOMAXCONN );
		}

		boolean TCPServerSocket::accept( SocketData& remoteSocketData, int waitTime )
		{
			if( waitTime >= 0 )
			{
				fd_set reads;
				FD_ZERO( &reads );
				FD_SET( socketData.fd, &reads );
				timeval time;
				time.tv_sec = waitTime / 1000;
				time.tv_usec = waitTime % 1000;
				select( 0, &reads, 0, 0, &time );
				if( !FD_ISSET( socketData.fd, &reads ) )
				{
					return false;
				}
			}

			remoteSocketData.fd = NEUTRON_INVALID_FD;
			sockaddr_in sockAddr;
			int sockAddrSize = sizeof( sockAddr );
			remoteSocketData.fd = ::accept( socketData.fd, (SOCKADDR*)&sockAddr, &sockAddrSize );
			remoteSocketData.netAddress.setINetAddress( sockAddr.sin_addr.s_addr );
			remoteSocketData.netAddress.setINetPort( sockAddr.sin_port );
			remoteSocketData.socketType = SOCKET_TYPE_STREAM;

			return remoteSocketData.fd != NEUTRON_INVALID_FD;
		}

		// TCP client socket
		TCPClientSocket::TCPClientSocket()
			:block( false )
			, connected( false )

		{
			remoteSocketData.fd = NEUTRON_INVALID_FD;
		}

		TCPClientSocket::~TCPClientSocket()
		{
		}

		boolean TCPClientSocket::connect( const char* address, int port, boolean blocking )
		{
			// create socket
			remoteSocketData.fd = NEUTRON_INVALID_FD;
			remoteSocketData.netAddress.setAddress( address );
			remoteSocketData.netAddress.setPort( port );
			remoteSocketData.socketType = SOCKET_TYPE_STREAM;

			remoteSocketData.fd = socket( AF_INET, SOCK_STREAM, 0 );
			if( remoteSocketData.fd == NEUTRON_INVALID_FD )
			{
				return false;
			}

			// set control parameter
			u_long nonBlocking = blocking ? 0 : 1;
			int ret = ioctlsocket( remoteSocketData.fd, FIONBIO, &nonBlocking );
			if( ret != 0 )
			{
				disconnect();
				return false;
			}
			block = blocking;

			// connect
			sockaddr_in connectSocketAddr;
			connectSocketAddr.sin_family = AF_INET;
			connectSocketAddr.sin_addr.s_addr = remoteSocketData.netAddress.getINetAddress();
			connectSocketAddr.sin_port = remoteSocketData.netAddress.getINetPort();
			ret = ::connect( remoteSocketData.fd, (sockaddr*)&connectSocketAddr, sizeof( connectSocketAddr ) );
			if( ret != 0 )
			{
				disconnect();
				return false;
			}

			timeval time;
			time.tv_sec = 0;
			time.tv_usec = 0;

			fd_set reads;
			FD_ZERO( &reads );
			FD_SET( remoteSocketData.fd, &reads );
			ret = ::select( 0, &reads, &reads, 0, &time );
			connected = ret > 0;
			return connected;
		}

		void TCPClientSocket::disconnect()
		{
			if( remoteSocketData.fd == NEUTRON_INVALID_FD )
			{
				closesocket( remoteSocketData.fd );
				remoteSocketData.fd = NEUTRON_INVALID_FD;
			}

			connected = false;
		}

		int TCPClientSocket::send( uint8* buffer, Size size, Size* sentSize )
		{
			int ret = ::send( remoteSocketData.fd, (char*)buffer, (int)size, 0 );
			int retError = SOCKET_RETURN_OK;
			if( ret < 0 )
			{
				int wsaError = WSAGetLastError();
				switch( wsaError )
				{
				case WSAEWOULDBLOCK:
					retError = SOCKET_RETURN_BLOCK; break;
				case WSAECONNRESET:
					retError = SOCKET_RETURN_LOST_CONNECTION; break;
				default:
					retError = SOCKET_RETURN_ERROR_UNKNOWN;
				}

				if( sentSize )
				{
					*sentSize = 0;
				}

				connected = false;
			}
			else
			{
				retError = SOCKET_RETURN_OK;
				if( sentSize )
				{
					*sentSize = ret;
				}
			}

			return retError;
		}

		int TCPClientSocket::recv( uint8* buffer, Size size, Size* receivedSize, int waitTime )
		{
			if( waitTime >= 0 )
			{
				fd_set reads;
				FD_ZERO( &reads );
				FD_SET( remoteSocketData.fd, &reads );
				timeval time;
				time.tv_sec = waitTime / 1000;
				time.tv_usec = waitTime % 1000;
				select( 0, &reads, 0, 0, &time );
				if( !FD_ISSET( remoteSocketData.fd, &reads ) )
				{
					return SOCKET_RETURN_NOTHING;
				}
			}

			int ret = ::recv( remoteSocketData.fd, (char*)buffer, (int)size, 0 );

			int retError = SOCKET_RETURN_OK;
			if( ret <= 0 )
			{
				if( ret == 0 )
				{
					retError = SOCKET_RETURN_REMOTE_CLOSED;
				}
				else
				{
					int wsaError = WSAGetLastError();
					switch( wsaError )
					{
					case WSAEWOULDBLOCK:
						retError = SOCKET_RETURN_BLOCK; break;
					case WSAECONNRESET:
						retError = SOCKET_RETURN_LOST_CONNECTION; break;
					default:
						retError = SOCKET_RETURN_ERROR_UNKNOWN;
					}
				}

				if( receivedSize )
				{
					*receivedSize = 0;
				}

				connected = false;
			}
			else
			{
				retError = SOCKET_RETURN_OK;
				if( receivedSize )
				{
					*receivedSize = ret;
				}
			}

			return retError;
		}

		Size TCPClientSocket::read( uint8* buffer, Size size )
		{
			Size receivedSize = 0;
			recv( buffer, size, &receivedSize );
			return receivedSize;
		}

		Size TCPClientSocket::write( uint8* buffer, Size size )
		{
			Size sentSize = 0;
			send( buffer, size, &sentSize );
			return sentSize;
		}

		// TCP session socket
		TCPSessionSocket::TCPSessionSocket()
			: block( false )
			, connected( false )
		{
			socketData.fd = NEUTRON_INVALID_FD;
		}

		TCPSessionSocket::~TCPSessionSocket()
		{
		}

		boolean TCPSessionSocket::init( const SocketData& setSocketData, boolean blocking )
		{
			// create socket
			assert( setSocketData.fd != NEUTRON_INVALID_FD && setSocketData.socketType == SOCKET_TYPE_STREAM );
			socketData.fd = setSocketData.fd;
			socketData.netAddress = setSocketData.netAddress;

			// set control parameter
			u_long nonBlocking = blocking ? 0 : 1;
			int ret = ioctlsocket( socketData.fd, FIONBIO, &nonBlocking );
			if( ret != 0 )
			{
				release();
			}

			connected = ( ret == 0 );

			return connected;
		}

		void TCPSessionSocket::release()
		{
			if( socketData.fd != NEUTRON_INVALID_FD )
			{
				closesocket( socketData.fd );
				socketData.fd = NEUTRON_INVALID_FD;
			}
		}

		int TCPSessionSocket::send( uint8* buffer, Size size, Size* sentSize )
		{
			int ret = ::send( socketData.fd, (char*)buffer, (int)size, 0 );
			int retError = SOCKET_RETURN_OK;
			if( ret < 0 )
			{
				int wsaError = WSAGetLastError();
				switch( wsaError )
				{
					case WSAEWOULDBLOCK:
					retError = SOCKET_RETURN_BLOCK; break;
					case WSAECONNRESET:
					retError = SOCKET_RETURN_LOST_CONNECTION; break;
					default:
					retError = SOCKET_RETURN_ERROR_UNKNOWN;
				}

				if( sentSize )
				{
					*sentSize = 0;
				}

				connected = false;
			}
			else
			{
				retError = SOCKET_RETURN_OK;
				if( sentSize )
				{
					*sentSize = ret;
				}
			}

			return retError;
		}

		int TCPSessionSocket::recv( uint8* buffer, Size size, Size* receivedSize, int waitTime )
		{
			if( waitTime >= 0 )
			{
				fd_set reads;
				FD_ZERO( &reads );
				FD_SET( socketData.fd, &reads );
				timeval time;
				time.tv_sec = waitTime / 1000;
				time.tv_usec = waitTime % 1000;
				select( 0, &reads, 0, 0, &time );
				if( !FD_ISSET( socketData.fd, &reads ) )
				{
					return SOCKET_RETURN_NOTHING;
				}
			}
			
			int ret = ::recv( socketData.fd, (char*)buffer, (int)size, 0 );
			int retError = SOCKET_RETURN_OK;
			if( ret <= 0 )
			{
				if( ret == 0 )
				{
					retError = SOCKET_RETURN_REMOTE_CLOSED;
				}
				else
				{
					int wsaError = WSAGetLastError();
					switch( wsaError )
					{
					case WSAEWOULDBLOCK:
						retError = SOCKET_RETURN_BLOCK; break;
					case WSAECONNRESET:
						retError = SOCKET_RETURN_LOST_CONNECTION; break;
					default:
						retError = SOCKET_RETURN_ERROR_UNKNOWN;
					}
				}

				if( receivedSize )
				{
					*receivedSize = 0;
				}

				connected = false;
			}
			else
			{
				retError = SOCKET_RETURN_OK;
				if( receivedSize )
				{
					*receivedSize = ret;
				}
			}

			return retError;
		}

		Size TCPSessionSocket::read( uint8* buffer, Size size )
		{
			Size receivedSize = 0;
			recv( buffer, size, &receivedSize );
			return receivedSize;
		}

		Size TCPSessionSocket::write( uint8* buffer, Size size )
		{
			Size sentSize = 0;
			send( buffer, size, &sentSize );
			return sentSize;
		}
	}
}