#pragma once

#include "NeutronFoundationCommon.h"
#include "Stream.h"
#include "Hash.h"

using Neutron::Utility::Stream;

namespace Neutron
{
	namespace Network
	{
		enum : int
		{
			SOCKET_TYPE_UNKNOWN = 0,
			SOCKET_TYPE_STREAM = 1,
			SOCKET_TYPE_DGRAM = 2
		};

		enum : int
		{
			SOCKET_RETURN_OK,
			SOCKET_RETURN_NOTHING,
			SOCKET_RETURN_BLOCK,
			SOCKET_RETURN_REMOTE_CLOSED,
			SOCKET_RETURN_LOST_CONNECTION,
			SOCKET_RETURN_ERROR_UNKNOWN
		};

		class NEUTRON_FOUNDATION_CORE NetAddress
		{
			uint32	address;
			uint16	port;

		public:
			NetAddress() {};
			NetAddress( const char* address_, int port_ ) { setAddress( address_ ); setPort( port_ ); };
			NetAddress( const NetAddress& other ) : address( other.address ), port( other.port ) {}
			virtual ~NetAddress() {}

			NetAddress& operator=( const NetAddress& rhs ) { address = rhs.address; port = rhs.port; return *this; }
			
			inline void setAddress( const char* addressString ) { address = inet_addr( addressString ); }
			inline void setPort( int portInt ) { port = htons( portInt ); }
			inline const char* getAddress() const { return inet_ntoa( *(in_addr*)( &address ) ); }
			inline int getPort() const { return ntohs( port ); }
			inline void setINetAddress( uint32 addressUInt32 ) { address = addressUInt32; }
			inline void setINetPort( uint16 portUInt16 ) { port = portUInt16; }
			inline uint32 getINetAddress() const { return address; }
			inline uint16 getINetPort() const { return port; }
			inline void reset() { address = 0; port = 0; }
			inline boolean valid() const { return address != 0 && port != 0; }
			inline uint32 getHashValue() const { return Math::Hash::DJB32( reinterpret_cast<const char*>( &address ), sizeof( address ) + sizeof( port ) ); }
			static uint32 getHashValue( const char* address, int port ) { return NetAddress( address, port ).getHashValue(); }
		};

		typedef struct
		{
			uintptr		fd;
			int			socketType;
			NetAddress	netAddress;
		}SocketData;

		NEUTRON_FOUNDATION_CORE boolean init();
		NEUTRON_FOUNDATION_CORE void release();

		// UDP socket
		class NEUTRON_FOUNDATION_CORE UDPSocket
		{
			SocketData		socketData;
			boolean			block;

		public:
			UDPSocket();
			virtual ~UDPSocket();

			boolean init( const char* address, int port, boolean block = true );
			void release();

			int send( const char* remoteAddress, int port, uint8* buffer, Size size, Size* sentSize = 0 );
			inline int send( const NetAddress& remoteNetAddress, uint8* buffer, Size size, Size* sentSize )
			{
				return send( remoteNetAddress.getAddress(), remoteNetAddress.getPort(), buffer, size, sentSize );
			}

			int recv( uint8* buffer, Size size, NetAddress* remoteAddress, Size* receivedSize = 0, int waitTime = -1 );

			const NetAddress& address() const { return socketData.netAddress; }
			inline boolean isBlock() const { return block; }
		};

		// TCP server socket
		class NEUTRON_FOUNDATION_CORE TCPServerSocket
		{
			SocketData		socketData;
			boolean			block;

		public:
			TCPServerSocket();
			virtual ~TCPServerSocket();

			boolean init( const char* address, int port, boolean block = true );
			void release();

			void listen( int maxConnectionCount = 0 );
			boolean accept( SocketData& remoteSocketData, int waitTime = -1 );

			inline const NetAddress& getNetAddress() const { return socketData.netAddress; }
			inline boolean isBlock() const { return block; }
		};

		// TCP client socket
		class NEUTRON_FOUNDATION_CORE TCPClientSocket : public Stream
		{
			SocketData		remoteSocketData;
			boolean			block;
			boolean			connected;

		public:
			TCPClientSocket();
			virtual ~TCPClientSocket();

			boolean connect( const char* address, int port, boolean block = true );
			void disconnect();

			int send( uint8* buffer, Size size, Size* sentSize = 0 );
			int recv( uint8* buffer, Size size, Size* receivedSize = 0, int waitTime = -1 );

			virtual Size read( uint8* buffer, Size size );
			virtual Size write( uint8* buffer, Size size );

			inline const NetAddress& getRemoteNetAddress() const { return remoteSocketData.netAddress; }
			inline boolean isBlock() const { return block; }
			inline boolean isConnected() const { return connected; }
		};

		// TCPSessionSocket
		class NEUTRON_FOUNDATION_CORE TCPSessionSocket : public Stream
		{
			SocketData		socketData;
			boolean			block;
			boolean			connected;

		public:
			TCPSessionSocket();
			virtual ~TCPSessionSocket();

			boolean init( const SocketData& socketData, boolean block = true );
			void release();

			int send( uint8* buffer, Size size, Size* sentSize = 0 );
			int recv( uint8* buffer, Size size, Size* receivedSize = 0, int waitTime = -1 );

			virtual Size read( uint8* buffer, Size size );
			virtual Size write( uint8* buffer, Size size );

			inline const NetAddress& getNetAddress() const { return socketData.netAddress; }
			inline boolean isBlock() const { return block; }
			inline boolean isConnected() const { return connected; }
		};
	}
}