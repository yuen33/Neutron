#pragma once

#include "NeutronFoundationCommon.h"
#include "String.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE Stream
		{
		public:
			Stream();
			virtual ~Stream();

			virtual Size read( uint8* buffer, Size size ) = 0;
			virtual Size write( uint8* buffer, Size size ) = 0;

			boolean readBoolean();
			int32 readInt32();
			int64 readInt64();
			uint8 readUInt8();
			uint32 readUInt32();
			uint64 readUInt64();
			float readFloat();
			double readDouble();
			String readString();

			void writeBoolean( boolean value );
			void writeInt32( int32 value );
			void writeInt64( int64 value );
			void writeUInt8( uint8 value );
			void writeUInt32( uint32 value );
			void writeUInt64( uint64 value );
			void writeFloat( float value );
			void writeDouble( double value );
			void writeString( const char* value );
		};
	}
}