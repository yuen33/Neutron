#pragma once

#include "CalculationScalar.h"

namespace Neutron
{
	namespace Math
	{
		template<typename T>
		class Vector4
		{
			T x;
			T y;
			T z;
			T w;

			inline Vector4() : x( 0 ), y( 0 ), z( 0 ), w( 0 ) {}
			inline Vector4( const T x, const T y, const T z, const T w ) : x( x ), y( y ), z( z ), w( w ) {}
			inline Vector4( const Vector4& other ) : x( other.x ), y( other.y ), z( other.z ), w( other.w ) {}
			inline explicit Vector4( const Vector2& other, const T vz, const T vw ) : x( other.x ), y( other.y ), z( vz ), w( vw ) {}
			inline explicit Vector4( const T vx, const Vector2& other, const T vw ) : x( other.x ), y( other.x ), z( other.y ), w( vw ) {}
			inline explicit Vector4( const T vx, const T vy, const Vector2& other ) : x( vx ), y( vy ), z( other.x ), w( other.y ) {}
			inline explicit Vector4( const Vector2& other0, const Vector2& other1 ) : x( other0.x ), y( other0.y ), z( other1.x ), w( other1.y ) {}
			inline explicit Vector4( const Vector3& other, const T vw ) : x( other.x ), y( other.y ), z( other.z ), w( vw ) {}
			inline explicit Vector4( const T vx, const Vector3& other ) : x( vx ), y( other.x ), z( other.y ), w( other.z ) {}
			~Vector4() {}

			inline Vector4& operator=( const Vector4& rhs ) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; }
			inline T& operator[]( int index ) { assert( index < 4 ); return *( &x + index ); }
			inline T operator[]( int index ) const { assert( index < 4 ); return *( &x + index ); }
			inline const T* data() { return &x; }

			inline Vector3& zero() { x = 0; y = 0; z = 0; return *this; }
			inline Vector3& flip() { x = -x; y = -y; z = -z; w = -w; return *this; }
			inline Vector3& operator-() const { return Vector4( -x, -y, -z, -w ); }
			inline Vector3& normalize() { T rlen = rcpSqrtSafe( x * x + y * y + z * z + w * w ); x *= rlen; y *= rlen; z *= rlen; return *this; }
			inline Vector3 getNormalized() const { T rlen = rcpSqrtSafe( x * x + y * y + z * z + w * w ); return ( *this * rlen ); }
			inline T length() const { return sqrt( x * x + y * y + z * z + w * w ); }
			inline T length2() const { return x * x + y * y + z * z + w * w; }

			inline boolean isZero( const T e ) const { return abs( x ) < e && abs( y ) < e && abs( z ) < e && abs( w ) < e; }
		};

		typedef Vector4<int> int4;
		typedef Vector4<float> float4;
		typedef Vector4<double> double4;
	}
}