#include "Stream.h"

namespace Neutron
{
	namespace Utility
	{
		Stream::Stream()
		{
		}

		Stream::~Stream()
		{
		}

		boolean Stream::readBoolean()
		{
			boolean ret;
			read( reinterpret_cast<uint8*>( &ret ), sizeof( boolean ) );
			return ret;
		}

		int32 Stream::readInt32()
		{
			int32 ret;
			read( reinterpret_cast<uint8*>( &ret ), sizeof( int32 ) );
			return ret;
		}

		int64 Stream::readInt64()
		{
			int64 ret;
			read( reinterpret_cast<uint8*>( &ret ), sizeof( uint64 ) );
			return ret;
		}

		uint8 Stream::readUInt8()
		{
			uint8 ret;
			read( &ret, sizeof( uint8 ) );
			return ret;
		}

		uint32 Stream::readUInt32()
		{
			uint32 ret;
			read( reinterpret_cast<uint8*>( &ret ), sizeof( uint32 ) );
			return ret;
		}

		uint64 Stream::readUInt64()
		{
			uint64 ret;
			read( reinterpret_cast<uint8*>( &ret ), sizeof( uint64 ) );
			return ret;
		}

		float Stream::readFloat()
		{
			float ret;
			read( reinterpret_cast<uint8*>( &ret ), sizeof( float ) );
			return ret;
		}

		double Stream::readDouble()
		{
			double ret;
			read( reinterpret_cast<uint8*>( &ret ), sizeof( double ) );
			return ret;
		}

		String Stream::readString()
		{
			uint32 length;
			read( reinterpret_cast<uint8*>( &length ), sizeof( uint32 ) );
			char* line = new char[length];
			assert( line );
			read( reinterpret_cast<uint8*>( line ), length * sizeof( char ) );
			delete [] line;
			return String( line );
		}

		void Stream::writeBoolean( boolean value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( boolean ) );
		}

		void Stream::writeInt32( int32 value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( int32 ) );
		}

		void Stream::writeInt64( int64 value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( int64 ) );
		}

		void Stream::writeUInt8( uint8 value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( uint8 ) );
		}

		void Stream::writeUInt32( uint32 value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( uint32 ) );
		}

		void Stream::writeUInt64( uint64 value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( uint64 ) );
		}

		void Stream::writeFloat( float value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( float ) );
		}

		void Stream::writeDouble( double value )
		{
			write( reinterpret_cast<uint8*>( &value ), sizeof( double ) );
		}

		void Stream::writeString( const char* value )
		{
			String line = value;
			uint32 length = line.getCount();
			write( reinterpret_cast<uint8*>( &length ), sizeof( uint32 ) );
			write( reinterpret_cast<uint8*>( &line[0] ), length * sizeof( char ) );
		}
	}
}