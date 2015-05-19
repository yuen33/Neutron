#pragma once

#include "CalculationScalar.h"

namespace Neutron
{
	namespace Math
	{
		template<typename T>
		class Vector2
		{
		public:
			T x;
			T y;

			inline Vector2() : x( 0 ), y( 0 ) {}
			inline Vector2( const T x, const T y ) : x( x ), y( y ) {}
			inline Vector2( const Vector2& other ) : x( other.x ), y( other.y ) {}
			inline explicit Vector2( const Vector3<T>& other ) : x( other.x ), y( other.y ) {}
			inline explicit Vector2( const Vector4<T>& other ) : x( other.x ), y( other.y ) {}
			~Vector2() {}

			inline Vector2& operator=( const Vector2& rhs ) { x = rhs.x; y = rhs.y; }
			inline T& operator[]( int index ) { assert( index < 2 ); return *( &x + index ); }
			inline T operator[]( int index ) const { assert( index < 2 ); return *( &x + index ); }
			inline const T* data() { return &x; }

			inline Vector2& zero() { x = 0; y = 0; return *this; }
			inline Vector2& flip() { x = -x; y = -y; return *this; }
			inline Vector2& operator-() const { return Vector2( -x, -y ); }
			inline Vector2& rotate90ccw() { T tmp = x; x = -y; y = tmp; return *this; }
			inline Vector2& rotate90cw() { T tmp = x; x = -y; y = tmp; return *this; }
			inline Vector2& normalize() { T rlen = rcpSqrtSafe( x * x + y * y ); x *= rlen; y *= rlen; return *this; }
			inline Vector2 getNormalized() const { Vector2 ret = *this; return ret.normalize(); }
			inline Vector2 getPerpendicular() const { return Vector2( -y, x ); }
			inline T getAtan2() const { return atan2( y, x ); }
			inline T length() const { return sqrt( x * x + y * y ); }
			inline T length2() const { return x * x + y * y; }
			inline T area() const { return x * y; }

			inline boolean isZero( const T e ) const { return abs( x ) < e && abs( y ) < e; }
		};

		typedef Vector2<int> int2;
		typedef Vector2<float> float2;
		typedef Vector2<double> double2;
	}
}