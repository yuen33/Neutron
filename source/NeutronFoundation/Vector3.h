#pragma once

#include "CalculationScalar.h"

namespace Neutron
{
	namespace Math
	{
		template<typename T>
		class Vector3
		{
		public:
			T x;
			T y;
			T z;

			inline Vector3() : x( 0 ), y( 0 ), z( 0 ) {}
			inline Vector3( const T x, const T y, const T z ) : x( x ), y( y ), z( z ) {}
			inline Vector3( const Vector3& other ) : x( other.x ), y( other.y ) {}
			inline explicit Vector3( const Vector2<T>& other, const T vz ) : x( other.x ), y( other.y ), z( vz ) {}
			inline explicit Vector3( const T vx, const Vector2<T>& other ) : x( vx ), y( other.x ), z( other.y ) {}
			inline explicit Vector3( const Vector4<T>& other ) : x( other.x ), y( other.y ), z( other.z ) {}
			~Vector3() {}

			inline Vector3& operator=( const Vector3& rhs ) { x = rhs.x; y = rhs.y; }
			inline T& operator[]( int index ) { assert( index < 3 ); return *( &x + index ); }
			inline T operator[]( int index ) const { assert( index < 3 ); return *( &x + index ); }
			inline const T* data() { return &x; }

			inline Vector3& zero() { x = 0; y = 0; z = 0; return *this; }
			inline Vector3& flip() { x = -x; y = -y; z = -z; return *this; }
			inline Vector3& operator-() const { return Vector3( -x, -y, -z ); }
			inline Vector3& normalize() { T rlen = rcpSqrtSafe( x * x + y * y + z * z ); x *= rlen; y *= rlen; z *= rlen; return *this; }
			inline Vector3 getNormalized() const { T rlen = rcpSqrtSafe( x * x + y * y + z * z ); return ( *this * rlen ); }
			inline T length() const { return sqrt( x * x + y * y + z * z ); }
			inline T length2() const { return x * x + y * y + z * z; }
			inline T volumn() const { return x * y * z; }

			inline boolean isZero( const T e ) const { return abs( x ) < e && abs( y ) < e && abs( z ) < e; }
			static Vector3 null;
		};

		template<typename T>
		Vector3<T> Vector3<T>::null = Vector3<T>();

		typedef Vector3<int> int3;
		typedef Vector3<float> float3;
		typedef Vector3<double> double3;
	}
}