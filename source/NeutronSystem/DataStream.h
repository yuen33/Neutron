#pragma once

#include "NeutronSystemCommon.h"
#include "NeutronFoundation/HashMap.h"
#include "NeutronFoundation/String.h"
#include "NeutronFoundation/AsyncQueue.h"
#include "Variable.h"
#include "DataFrame.h"

using Neutron::Container::HashMap;
using Neutron::Container::String;
using Neutron::Container::AsyncQueue;

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE DataStream : public RCObject
		{
			HashMap<uint32, VariablePtr>		variables;
			AsyncQueue<DataFramePtr>			frames;

		public:
			DataStream();
			virtual ~DataStream();
		};
	}
}