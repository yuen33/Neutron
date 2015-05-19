#pragma once

#include "MathDefine.h"

namespace Neutron
{
	namespace Math
	{
#ifdef min
#undef min
#endif
		template<typename T>
		inline T min( const T& lhs, const T& rhs )
		{
			return lhs < rhs ? lhs : rhs;
		}

#ifdef max
#undef max
#endif
		template<typename T>
		inline T max( const T& lhs, const T& rhs )
		{
			return lhs < rhs ? rhs : lhs;
		}

		template<typename T>
		inline T clamp( const T& x, const T& min, const T& max )
		{
			return x < min ? min : x < max ? x : max;
		}

		template<typename T>
		inline void limit( T& x, const T& min, const T& max )
		{
			if( x < min ) x = min;
			if( x > max ) x = max;
		}

		template<typename T>
		inline T abs( const T& x )
		{
			return x < 0 ? -x : x;
		}

		static inline boolean isNAN( float x )
		{
			return x != x;
		}

		static inline boolean isNAN( double x )
		{
			return x != x;
		}

		static inline boolean isINF( float x )
		{
			return x < NEUTRON_FLT_MIN || x > NEUTRON_FLT_MAX;
		}

		static inline boolean isINF( double x )
		{
			return x < NEUTRON_DBL_MIN || x > NEUTRON_DBL_MAX;
		}

		static inline boolean validate( float x )
		{
			return !isNAN( x ) && !isINF( x );
		}

		static inline boolean validate( double x )
		{
			return !isNAN( x ) && !isINF( x );
		}

		static inline boolean compare( float lhs, float rhs )
		{
			float v = abs( lhs - rhs );
			return v < Epsilon;
		}

		static inline boolean compare( double lhs, double rhs )
		{
			double v = abs( lhs - rhs );
			return v < Epsilon;
		}

		static inline float ceil( float x )
		{
			return ::ceilf( x );
		}

		static inline double ceil( double x )
		{
			return ::ceil( x );
		}

		static inline float floor( float x )
		{
			return ::floorf( x );
		}

		static inline double floor( double x )
		{
			return ::floor( x );
		}

		static inline float sqrt( float x )
		{
#if defined( NEUTRON_WINDOWS_DESKTOP ) && defined( NEUTRON_BUILD_ARCH_IX86 )
			__m128 s = _mm_sqrt_ss( _mm_set_ss( x ) );
			float r;
			_mm_store_ss( &r, s );
			return r;
#else
			return ::sqrtf( x );
#endif
		}

		static inline double sqrt( double x )
		{
			return ::sqrt( x );
		}

		static inline double sqrtFast( float x )
		{
			IntFloat i = x;
			i.i = 0x5f3759df - ( i.i >> 1 );
			x = i.f * x;
			return x * ( 1.5f - ( i.f * x * 0.5f ) );
		}

		static inline float rcp( float x )
		{
			return 1.0f / x;
		}

		static inline double rcp( double x )
		{
			return 1.0 / x;
		}

		static inline float rcpFast( float x )
		{
#if defined( NEUTRON_WINDOWS_DESKTOP ) && defined( NEUTRON_BUILD_ARCH_IX86 )
			__m128 s = _mm_rcp_ss( _mm_set_ss( x ) );
			float r;
			_mm_store_ss( &r, s );
			return r;
#else
			IntFloat i = x;
			i.i = 0x7f000000 - i.i;
			return i.f * ( 2.0f - x * i.f );
#endif
		}

		static inline float rcpSqrt( float x )
		{
			return 1.0f / ::sqrtf( x );
		}

		static inline double rcpSqrt( double x )
		{
			return 1.0 / ::sqrt( x );
		}

		static inline float rcpSqrtFast( float x )
		{
#if defined( NEUTRON_WINDOWS_DESKTOP ) && defined( NEUTRON_BUILD_ARCH_IX86 )
			__m128 s = _mm_rsqrt_ss( _mm_set_ss( x ) );
			float r;
			_mm_store_ss( &r, s );
			return r;
#else
			IntFloat i = x;
			i.i = 0x5f3759df - ( i.i >> 1 );
			return i.f * ( 1.5f - ( i.f * i.f * x * 0.5f ) );
#endif
		}

		static inline float rcpSqrtSafe( float x )
		{
			return 1.0f / sqrtf( x + NEUTRON_FLT_MIN );
		}

		static inline double rcpSqrtSafe( double x )
		{
			return 1.0 / sqrt( x + NEUTRON_DBL_MIN );
		}

		static inline float mod( float x, float y )
		{
			return ::fmodf( x, y );
		}

		static inline double mod( double x, double y )
		{
			return ::fmod( x, y );
		}

		static inline float pow( float x, float y )
		{
			return ::powf( x, y );
		}

		static inline double pow( double x, double y )
		{
			return ::pow( x, y );
		}

		static inline float exp( float x )
		{
			return ::expf( x );
		}

		static inline double exp( double x )
		{
			return ::exp( x );
		}

		static inline float log( float x )
		{
			return ::logf( x );
		}

		static inline double log( double x )
		{
			return ::log( x );
		}

		static inline float rad2Deg( float x )
		{
			return x * PI / 180.0f;
		}

		static inline double rad2Deg( double x )
		{
			return x * PI / 180.0f;
		}

		static inline float deg2Rad( float x )
		{
			return x * 180.0f / PI;
		}

		static inline double deg2Rad( double x )
		{
			return x * 180.0 / PI;
		}

		static inline float sin( float x )
		{
			return ::sinf( x );
		}

		static inline double sin( double x )
		{
			return ::sin( x );
		}

		static inline float cos( float x )
		{
			return ::cosf( x );
		}

		static inline double cos( double x )
		{
			return ::cos( x );
		}

		static inline float tan( float x )
		{
			return ::tanf( x );
		}

		static inline double tan( double x )
		{
			return ::tan( x );
		}

		static inline float asin( float x )
		{
			return ::asinf( x );
		}

		static inline double asin( double x )
		{
			return ::asin( x );
		}

		static inline float acos( float x )
		{
			return ::acosf( x );
		}

		static inline double acos( double x )
		{
			return ::acos( x );
		}

		static inline float atan( float x )
		{
			return ::atanf( x );
		}

		static inline double atan( double x )
		{
			return ::atan( x );
		}

		static inline float atan2( float y, float x )
		{
			return ::atan2f( y, x );
		}

		static inline double atan2( double y, double x )
		{
			return ::atan2( y, x );
		}

		static inline void sincos( float x, float &s, float&c )
		{
#if defined( NEUTRON_WINDOWS_DESKTOP ) && defined( NEUTRON_BUILD_ARCH_IX86 )
			_asm
			{
				fld x
				fsincos
				mov edx, s
				mov ecx, c
				fstp dword ptr [ecx]
				fstp dword ptr [edx]
			}
#else
			s = ::sinf( x );
			c = ::cosf( x );
#endif
		}

		static inline void sincos( double x, double& s, double& c )
		{
#if defined( NEUTRON_WINDOWS_DESKTOP ) && defined( NEUTRON_BUILD_ARCH_IX86 )
			__asm
			{
				fld x
				fsincos
				mov edx, s
				mov ecx, c
				fstp qword ptr[ecx]
				fstp qword ptr[edx]
			}
#else
			s = ::sin( x );
			c = ::cos( x );
#endif
		}

		static inline int round( float x )
		{
#if defined( NEUTRON_WINDOWS_DESKTOP ) && defined( NEUTRON_BUILD_ARCH_IX86 )
			int i;
			__asm
			{
				fld x
				fistp i
			}
			return i;
#else
			return static_cast<int>( x + 0.5f );
#endif
		}

		static inline int round( double x )
		{
			return static_cast<int>( x + 0.5 );
		}

		static inline float lerp( float p, float q, float k )
		{
			return p + ( q - p ) * k;
		}

		static inline double lerp( double p, double q, double k )
		{
			return p + ( q - p ) * k;
		}

		static inline float saturate( float x )
		{
			return x < 0.0f ? 0.0f : x < 1.0f ? x : 1.0f;
		}

		static inline double saturate( double x )
		{
			return x < 0.0 ? 0.0 : x < 1.0 ? x : 1.0;
		}
	}
}