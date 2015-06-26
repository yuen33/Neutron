#pragma once

#include "NeutronFoundation/RCPtr.h"

using Neutron::Utility::RCObject;
using Neutron::Utility::RCPtr;

namespace Neutron
{
	namespace Engine
	{
		// framework
		class DataFrame;
		class DataStream;
		class Pin;
		class Variable;
		class VPU;

		typedef RCPtr<DataFrame>		DataFramePtr;
		typedef RCPtr<DataStream>		DataStreamPtr;
		typedef RCPtr<Pin>				PinPtr;
		typedef RCPtr<Variable>			VariablePtr;
		typedef RCPtr<VPU>				VPUPtr;

		// resources
		class Image;

		typedef RCPtr<Image> ImagePtr;
	}
}