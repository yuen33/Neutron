#include "Pin.h"

namespace Neutron
{
	namespace Engine
	{
		Pin::Pin()
		{
		};

		Pin::Pin( int direction )
			: direction( direction )
		{
		}

		Pin::~Pin()
		{
		};

		void Pin::attach( ProcessingUnitPtr unit )
		{
		}

		void Pin::attach( ResourcePtr unit )
		{
		}

		void Pin::dettach()
		{
		}

		void Pin::getData( ProcessingUnitPtr& outData )
		{
			outData = ProcessingUnitPtr::null;
		}

		void Pin::getData( ResourcePtr& outData )
		{
			outData = ResourcePtr::null;
		}
	}
}