#pragma once

#include "Platform.h"

namespace Neutron
{
	namespace Math
	{
		static const float PI = 3.14159265358979323846264338327950288419716939937510f;
		static const float PI2 = PI * 2.0f;
		static const float PI05 = PI * 0.5f;
		static const float Epsilon = 1e-6f;

		union IntFloat
		{
			IntFloat() {}
			IntFloat( int i ) : i( i ) {}
			IntFloat( float f ) : f( f ) {}
			IntFloat( unsigned int ui ) : ui( ui ) {}
			int i;
			float f;
			unsigned ui;
		};

		union IntDouble
		{
			IntDouble() {}
			IntDouble( double d ) : d( d ) {}
			int i[2];
			double d;
			unsigned int ui[2];
		};

		template<typename T>
		class Vector2;
		template<typename T>
		class Vector3;
		template<typename T>
		class Vector4;
		template<typename T>
		class Matrix44;
	}
}