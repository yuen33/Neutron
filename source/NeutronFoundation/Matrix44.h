#pragma once

#include "CalculationScalar.h"

namespace Neutron
{
	namespace Math
	{
		template<typename T>
		class Matrix44
		{
		public:
			T m00, m01, m02, m03;
			T m10, m11, m12, m13;
			T m20, m21, m22, m23;
			T m30, m31, m32, m33;

			inline Matrix44()
				:m00( 0 ), m01( 0 ), m02( 0 ), m03( 0 )
				,m10( 0 ), m11( 0 ), m12( 0 ), m13( 0 )
				,m20( 0 ), m21( 0 ), m22( 0 ), m23( 0 )
				,m30( 0 ), m31( 0 ), m32( 0 ), m33( 0 )
			{}

			inline Matrix44(
				T m00, T m01, T m02, T m03,
				T m10, T m11, T m12, T m13,
				T m20, T m21, T m22, T m23,
				T m30, T m31, T m32, T m33
				)
				:m00( m00 ), m01( m01 ), m02( m02 ), m03( m03 )
				,m10( m10 ), m11( m11 ), m12( m12 ), m13( m13 )
				,m20( m20 ), m21( m21 ), m22( m22 ), m23( m23 )
				,m30( m30 ), m31( m31 ), m32( m32 ), m33( m33 )
			{}

			inline Matrix44( const Matrix44& o )
				:m00( o.m00 ), m01( o.m01 ), m02( o.m02 ), m03( o.m03 )
				,m10( o.m10 ), m11( o.m11 ), m12( o.m12 ), m13( o.m13 )
				,m20( o.m20 ), m21( o.m21 ), m22( o.m22 ), m23( o.m23 )
				,m30( o.m30 ), m31( o.m31 ), m32( o.m32 ), m33( o.m33 )
			{}

			inline Matrix44( const T* data )
				:m00( data[0] ), m01( data[1] ), m02( data[2] ), m03( data[3] )
				,m10( data[4] ), m11( data[5] ), m12( data[6] ), m13( data[7] )
				,m20( data[8] ), m21( data[9] ), m22( data[10] ), m23( data[11] )
				,m30( data[12] ), m31( data[13] ), m32( data[14] ), m33( data[15] )
			{}

			inline T& operator[]( int index ) { assert( index < 16 ); return *( &m00 + index ); }
			inline T operator[]( int index ) const { assert( index < 16 ); return *( &m00 + index ); }
			inline T& operator()( int i, int j ) { assert( i < 4 && j < 4 ); return *( &m00 + i * 4 + j ); }
			inline T operator()( int i, int j ) const { assert( i < 4 && j < 4 ); return *( &m00 + i * 4 + j ); }
			inline const T* data() { return &m00; }

			~Matrix44() {}

			inline Matrix44& zero()
			{
				m00 = 0; m01 = 0; m02 = 0; m03 = 0;
				m10 = 0; m11 = 0; m12 = 0; m13 = 0;
				m20 = 0; m21 = 0; m22 = 0; m23 = 0; 
				m30 = 0; m31 = 0; m32 = 0; m33 = 0;
				return *this;
			}

			inline Matrix44& identity()
			{
				m00 = 1; m01 = 0; m02 = 0; m03 = 0;
				m10 = 0; m11 = 1; m12 = 0; m13 = 0;
				m20 = 0; m21 = 0; m22 = 1; m23 = 0; 
				m30 = 0; m31 = 0; m32 = 0; m33 = 1;
				return *this;
			}
			
			inline Matrix44& transpose()
			{
				Matrix44 t = *this;
				m00 = t.m00; m01 = t.m10; m02 = t.m20; m03 = t.m30;
				m10 = t.m01; m11 = t.m11; m12 = t.m21; m13 = t.m31;
				m20 = t.m02; m21 = t.m12; m22 = t.m22; m23 = t.m32; 
				m30 = t.m03; m31 = t.m13; m32 = t.m23; m33 = t.m33;
				return *this;
			}

			inline Matrix44& getTransposed()
			{
				return Matrix44(
					m00, m10, m20, m30,
					m01, m11, m21, m31,
					m02, m12, m22, m32,
					m03, m13, m23, m33
					);
			}

			inline Matrix44& invert()
			{
				T t[12];
				Matrix44<T> m = *this;

				// calculate pairs for first 8 elements
				t[0] = m.m22 * m.m33;
				t[1] = m.m32 * m.m23;
				t[2] = m.m12 * m.m33;
				t[3] = m.m32 * m.m13;
				t[4] = m.m12 * m.m23;
				t[5] = m.m22 * m.m13;
				t[6] = m.m02 * m.m33;
				t[7] = m.m32 * m.m03;
				t[8] = m.m02 * m.m23;
				t[9] = m.m22 * m.m03;
				t[10]= m.m02 * m.m13;
				t[11]= m.m12 * m.m03;

				// calculate first 8 elements
				m00  = t[0] * m.m11 + t[3] * m.m21 + t[ 4] * m.m31;
				m00 -= t[1] * m.m11 + t[2] * m.m21 + t[ 5] * m.m31;
				m01  = t[1] * m.m01 + t[6] * m.m21 + t[ 9] * m.m31;
				m01 -= t[0] * m.m01 + t[7] * m.m21 + t[ 8] * m.m31;
				m02  = t[2] * m.m01 + t[7] * m.m11 + t[10] * m.m31;
				m02 -= t[3] * m.m01 + t[6] * m.m11 + t[11] * m.m31;
				m03  = t[5] * m.m01 + t[8] * m.m11 + t[11] * m.m21;
				m03 -= t[4] * m.m01 + t[9] * m.m11 + t[10] * m.m21;
				m10  = t[1] * m.m10 + t[2] * m.m20 + t[ 5] * m.m30;
				m10 -= t[0] * m.m10 + t[3] * m.m20 + t[ 4] * m.m30;
				m11  = t[0] * m.m00 + t[7] * m.m20 + t[ 8] * m.m30;
				m11 -= t[1] * m.m00 + t[6] * m.m20 + t[ 9] * m.m30;
				m12  = t[3] * m.m00 + t[6] * m.m10 + t[11] * m.m30;
				m12 -= t[2] * m.m00 + t[7] * m.m10 + t[10] * m.m30;
				m13  = t[4] * m.m00 + t[9] * m.m10 + t[10] * m.m20;
				m13 -= t[5] * m.m00 + t[8] * m.m10 + t[11] * m.m20;

				// calculate pairs for second 8 elements
				t[ 0] = m.m20 * m.m31;
				t[ 1] = m.m30 * m.m21;
				t[ 2] = m.m10 * m.m31;
				t[ 3] = m.m30 * m.m11;
				t[ 4] = m.m10 * m.m21;
				t[ 5] = m.m20 * m.m11;
				t[ 6] = m.m00 * m.m31;
				t[ 7] = m.m30 * m.m01;
				t[ 8] = m.m00 * m.m21;
				t[ 9] = m.m20 * m.m01;
				t[10] = m.m00 * m.m11;
				t[11] = m.m10 * m.m01;

				// calculate second 8 elements
				m20  = t[ 0] * m.m13 + t[ 3] * m.m23 + t[ 4] * m.m33;
				m20 -= t[ 1] * m.m13 + t[ 2] * m.m23 + t[ 5] * m.m33;
				m21  = t[ 1] * m.m03 + t[ 6] * m.m23 + t[ 9] * m.m33;
				m21 -= t[ 0] * m.m03 + t[ 7] * m.m23 + t[ 8] * m.m33;
				m22  = t[ 2] * m.m03 + t[ 7] * m.m13 + t[10] * m.m33;
				m22 -= t[ 3] * m.m03 + t[ 6] * m.m13 + t[11] * m.m33;
				m23  = t[ 5] * m.m03 + t[ 8] * m.m13 + t[11] * m.m23;
				m23 -= t[ 4] * m.m03 + t[ 9] * m.m13 + t[10] * m.m23;
				m30  = t[ 2] * m.m22 + t[ 5] * m.m32 + t[ 1] * m.m12;
				m30 -= t[ 4] * m.m32 + t[ 0] * m.m12 + t[ 3] * m.m22;
				m31  = t[ 8] * m.m32 + t[ 0] * m.m02 + t[ 7] * m.m22;
				m31 -= t[ 6] * m.m22 + t[ 9] * m.m32 + t[ 1] * m.m02;
				m32  = t[ 6] * m.m12 + t[11] * m.m32 + t[ 3] * m.m02;
				m32 -= t[10] * m.m32 + t[ 2] * m.m02 + t[ 7] * m.m12;
				m33  = t[10] * m.m22 + t[ 4] * m.m02 + t[ 9] * m.m12;
				m33 -= t[ 8] * m.m12 + t[11] * m.m22 + t[ 5] * m.m02;


				// calculate determinant
				T det = ( m.m00 * m00 + m.m10 * m01 + m.m20 * m02 + m.m30 * m03 );

				// divide the cofactor-matrix by the determinant
				T idet = (T)1.0 / det;
				m00 *= idet; m01 *= idet; m02 *= idet; m03 *= idet;
				m10 *= idet; m11 *= idet; m12 *= idet; m13 *= idet;
				m20 *= idet; m21 *= idet; m22 *= idet; m23 *= idet;
				m30 *= idet; m31 *= idet; m32 *= idet; m33 *= idet;

				return *this;
			}

			inline Matrix44 getInverted() const { return Matrix44 t = *this; return t.invert(); }
			static Matrix44 null;
		};

		template<typename T>
		Matrix44<T> Matrix44<T>::null = Matrix44<T>();

		typedef Matrix44<int> int4x4;
		typedef Matrix44<float> float4x4;
		typedef Matrix44<double> double4x4;
	}
}