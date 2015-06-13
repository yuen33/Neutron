#pragma once

#include "NeutronSystemCommon.h"
#include "EngineDefine.h"
#include "NeutronFoundation/Type.h"
#include "NeutronFoundation/String.h"
#include "NeutronFoundation/Vector2.h"
#include "NeutronFoundation/Vector3.h"
#include "NeutronFoundation/Vector4.h"
#include "NeutronFoundation/Matrix44.h"

using Neutron::Container::String;
using Neutron::Math::float2;
using Neutron::Math::float3;
using Neutron::Math::float4;
using Neutron::Math::float4x4;

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE Variable : RCObject
		{
		public:
			Variable() {};
			virtual ~Variable() {};

			virtual inline void set( const boolean& value ) { assert( 0 ); };
			virtual inline void set( const int32& value ) { assert( 0 ); };
			virtual inline void set( const int64& value ) { assert( 0 ); };
			virtual inline void set( const uint32& value ) { assert( 0 ); };
			virtual inline void set( const uint64& value ) { assert( 0 ); };
			virtual inline void set( const float& value ) { assert( 0 ); };
			virtual inline void set( const double& value ) { assert( 0 ); };
			virtual inline void set( const String& value ) { assert( 0 ); };
			virtual inline void set( const float2& value ) { assert( 0 ); };
			virtual inline void set( const float3& value ) { assert( 0 ); };
			virtual inline void set( const float4& value ) { assert( 0 ); };
			virtual inline void set( const float4x4& value ) { assert( 0 ); };

			virtual inline void get( boolean& value ) const { assert( 0 ); }
			virtual inline void get( int32& value ) const { assert( 0 ); }
			virtual inline void get( int64& value ) const { assert( 0 ); }
			virtual inline void get( uint32& value ) const { assert( 0 ); }
			virtual inline void get( uint64& value ) const { assert( 0 ); }
			virtual inline void get( float& value ) const { assert( 0 ); }
			virtual inline void get( double& value ) const { assert( 0 ); }
			virtual inline void get( String& value ) const { assert( 0 ); }
			virtual inline void get( float2& value ) const { assert( 0 ); }
			virtual inline void get( float3& value ) const { assert( 0 ); }
			virtual inline void get( float4& value ) const { assert( 0 ); }
			virtual inline void get( float4x4& value ) const { assert( 0 ); }

			virtual int getTypeID() const = 0;
			virtual Size getSize() const = 0;
		};

		template<typename T>
		class VariableConcrete
		{
			T						data;
		public:
			VariableConcrete();
			VariableConcrete( const VariableConcrete& other ) : data( other.data ) {}
			VariableConcrete( const T& value ) : data( value ) {}
			virtual ~VariableConcrete();

			VariableConcrete& operator=( const VariableConcrete& rhs ) { data = rhs.data; return *this; }
			VariableConcrete& operator=( const T& value ) { data = value; return *this; }
			T& operator()() { return data; }

			virtual inline int getTypeID() const { return Type::getTypeID<T>(); }
			virtual inline int getSize() const { return sizeof( T ); }
			inline T& getData() { return data; }
		};

		typedef VariableConcrete<boolean>				VarBoolen;
		typedef VariableConcrete<int32>					VarInt;
		typedef VariableConcrete<int64>					VarInt64;
		typedef VariableConcrete<uint32>				VarUInt32;
		typedef VariableConcrete<uint64>				VarUInt64;
		typedef VariableConcrete<float>					VarFloat;
		typedef VariableConcrete<double>				VarDouble;
		typedef VariableConcrete<String>				VarString;
		typedef VariableConcrete<float2>				VarFloat2;
		typedef VariableConcrete<float3>				VarFloat3;
		typedef VariableConcrete<float4>				VarFloat4;
		typedef VariableConcrete<float4x4>				VarFloat4x4;
	}
}