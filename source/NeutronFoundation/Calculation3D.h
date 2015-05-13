#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix43.h"
#include "matrix44.h"

namespace Neutron
{
	namespace Math
	{
		// vector2
		template<typename T>
		static inline Vector2<T> add( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs.x + rhs.x, lhs.y + rhs.y );
		}

		template<typename T>
		static inline Vector2<T> minus( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs.x - rhs.x, lhs.y - rhs.y );
		}

		template<typename T>
		static inline Vector2<T> mul( const Vector2<T>& lhs, const T& rhs )
		{
			return Vector2<T>( lhs.x * rhs, lhs.y * rhs );
		}

		template<typename T>
		static inline Vector2<T> mul( const T& lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs * rhs.x, lhs.y * rhs.y );
		}

		template<typename T>
		static inline T dot( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return lhs.x * rhs.y + lhs.y * rhs.x;
		}

		template<typename T>
		static inline T mul( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return dot( lhs, rhs );
		}

		template<typename T>
		static inline Vector2<T> cross( const Vector2<T>& lhs, const Vector2<T>& rhs )
		{
			return Vector2<T>( lhs.x * rhs.y - lhs.y * rhs.x );
		}

		template<typename T>
		static inline Vector2<T> clamp( const Vector2<T>& x, const Vector2<T>& min, const Vector2<T>& max )
		{
			return Vector2<T>( clamp( x.x, min.x, max.x ), clamp( x.y, min.y, max.y ) );
		}

		template<typename T>
		static inline Vector2<T> lerp( const Vector2<T>& p, const Vector2<T>& q, T k )
		{
			return add( mul( p, ( (T)1.0 -  k ),  mul( q, k ) ) );
		}

		template<typename T>
		static inline Vector2<T> slerp( const Vector2<T>& p, const Vector2<T>& q, T k )
		{
			assert( abs( 1 - ( p | p ) ) < Epsilon );
			assert( abs( 1 - ( q | q ) ) < Epsilon );

			Vector2<T> ret;
			T cosine = ( p | q );

			if( cosine >= (T)0.99 )
			{
				ret = lerp( p, q, k );
				ret.normalize();
			}
			else
			{
				T rad = acos( cosine );
				T scale0 = sin( ( 1 - k ) * rad );
				T scale1 = sin( k * rad );
				ret = ( p * scale0 + q * scale1 ) / sin( rad );
				ret.normalize();
			}

			return ret;
		}
	}
}