#pragma once

#include "NeutronSystemCommon.h"
#include "EngineDefine.h"
#include "NeutronFoundation/Type.h"
#include "NeutronFoundation/Array.h"
#include "NeutronFoundation/String.h"
#include "NeutronFoundation/Vector2.h"
#include "NeutronFoundation/Vector3.h"
#include "NeutronFoundation/Vector4.h"
#include "NeutronFoundation/Matrix44.h"

using Neutron::Container::Array;
using Neutron::Container::String;
using Neutron::Math::float2;
using Neutron::Math::float3;
using Neutron::Math::float4;
using Neutron::Math::float4x4;

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE DataFrame : public RCObject
		{
		public:
			DataFrame();
			virtual ~DataFrame();

			virtual int	getTypeID() const = 0;
			virtual Size getSize() const = 0;
		};
		
		template<typename T>
		class DataFrameConcrete : public DataFrame
		{
			T				data;

		public:
			DataFrameConcrete();
			virtual ~DataFrameConcrete();

			virtual inline int getTypeID() const { return Type::getTypeID<T>(); }
			virtual inline Size getSize() const { return sizeof( T ); }
			inline T& data() const { return data; }
		};

		typedef DataFrameConcrete<boolean>				DataFrameBoolen;
		typedef DataFrameConcrete<int32>				DataFrameInt;
		typedef DataFrameConcrete<int64>				DataFrameInt64;
		typedef DataFrameConcrete<uint32>				DataFrameUInt32;
		typedef DataFrameConcrete<uint64>				DataFrameUInt64;
		typedef DataFrameConcrete<float>				DataFrameFloat;
		typedef DataFrameConcrete<double>				DataFrameDouble;
		typedef DataFrameConcrete<String>				DataFrameString;
		typedef DataFrameConcrete<float2>				DataFrameFloat2;
		typedef DataFrameConcrete<float3>				DataFrameFloat3;
		typedef DataFrameConcrete<float4>				DataFrameFloat4;
		typedef DataFrameConcrete<float4x4>				DataFrameFloat4x4;

		typedef DataFrameConcrete<Array<boolean>>		DataFrameBooleanArray;
		typedef DataFrameConcrete<Array<boolean>>		DataFrameBoolenArray;
		typedef DataFrameConcrete<Array<int32>>			DataFrameIntArray;
		typedef DataFrameConcrete<Array<int64>>			DataFrameInt64Array;
		typedef DataFrameConcrete<Array<uint32>>		DataFrameUInt32Array;
		typedef DataFrameConcrete<Array<uint64>>		DataFrameUInt64Array;
		typedef DataFrameConcrete<Array<float>>			DataFrameFloatArray;
		typedef DataFrameConcrete<Array<double>>		DataFrameDoubleArray;
		typedef DataFrameConcrete<Array<String>>		DataFrameStringArray;
		typedef DataFrameConcrete<Array<float2>>		DataFrameFloat2Array;
		typedef DataFrameConcrete<Array<float3>>		DataFrameFloat3Array;
		typedef DataFrameConcrete<Array<float4>>		DataFrameFloat4Array;
		typedef DataFrameConcrete<Array<float4x4>>		DataFrameFloat4x4Array;
	}
}