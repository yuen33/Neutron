#pragma once

#include "NeutronSystemCommon.h"
#include "DataStream.h"

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE Pin : public RCObject
		{
			enum : int
			{
				Unknown,
				Input,
				Output,
			};

			int					direction;
			int					acceptTypeID;
			DataStreamPtr		stream;

		public:
			Pin() {};
			Pin( int direction, int acceptTypeID ) : direction( direction ), acceptTypeID( acceptTypeID ) {}
			virtual ~Pin() {};

			inline int getDirection() const { return direction; }
			inline int getAcceptTypeID() const { return acceptTypeID; }
			inline DataStreamPtr getStream() { return stream; }
			inline void setStream( DataStreamPtr stream_ ) { stream = stream_; }
		};
	}
}