#pragma once

#include "MathDefine.h"

namespace Neutron
{
	namespace Math
	{
		template<typename T>
		static inline Vector2<T> add( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs.x + rhs.x, lhs.y + rhs.y );
		}

		template<typename T>
		static inline Vector3<T> add( const Vector3<T>& lhs, const Vector3<T>& rhs )
		{
			return Vector3<T>( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z );
		}

		template<typename T>
		static inline Vector2<T> minus( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs.x - rhs.x, lhs.y - rhs.y );
		}

		template<typename T>
		static inline Vector3<T> minus( const Vector3<T>& lhs, const Vector3<T>& rhs )
		{
			return Vector3<T>( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z );
		}

		template<typename T>
		static inline Vector2<T> mul( const Vector2<T>& lhs, const T rhs )
		{
			return Vector2<T>( lhs.x * rhs, lhs.y * rhs );
		}

		template<typename T>
		static inline Vector3<T> mul( const Vector3<T>& lhs, const T rhs )
		{
			return Vector3<T>( lhs.x * rhs, lhs.y * rhs, lhs.z * rhs );
		}

		template<typename T>
		static inline Vector2<T> mul( const T lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs * rhs.x, lhs.y * rhs.y );
		}

		template<typename T>
		static inline Vector3<T> mul( const T lhs, const Vector3<T>& rhs )
		{
			return Vector3<T>( lhs * rhs.x, lhs * rhs.y, lhs * rhs.z );
		}

		template<typename T>
		static inline T dot( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		template<typename T>
		static inline T dot( const Vector3<T>& lhs, const Vector3<T>& rhs )
		{
			return lhs.x * rhs.y + lhs.y * rhs.x + lhs.z * rhs.z;
		}

		template<typename T>
		static inline Vector2<T> cross( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs.x * rhs.y - lhs.y * rhs.x );
		}

		template<typename T>
		static inline Vector3<T> cross( const Vector3<T>& lhs, const Vector3<T>& rhs )
		{
			return Vector3<T>(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x
				);
		}

		template<typename T>
		static inline Vector2<T> clamp( const Vector2<T>& x, const Vector2<T>& min, const Vector2<T>& max )
		{
			return Vector2<T>( clamp( x.x, min.x, max.x ), clamp( x.y, min.y, max.y ) );
		}

		template<typename T>
		static inline Vector3<T> clamp( const Vector3<T>& x, const Vector3<T>& min, const Vector3<T>& max )
		{
			return Vector3<T>( clamp( x.x, min.x, max.x ), clamp( x.y, min.y, max.y ), clamp( x.z, min.z, max.z );
		}

		template<typename T>
		static inline Vector2<T> lerp( const Vector2<T>& p, const Vector2<T>& q, T k )
		{
			return add( mul( p, ( (T)1.0 -  k ),  mul( q, k ) ) );
		}

		template<typename T>
		static inline Vector3<T> lerp( const Vector3<T>& p, const Vector3<T>& q, T k )
		{
			return add( mul( p, ( (T)1.0 - k ), mul( q, k ) ) );
		}
	}
}