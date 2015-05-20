#pragma once

#include "Platform.h"

namespace Neutron
{
	namespace Type
	{
		inline static const int generateTypeID()
		{
			static int id = 0;
			return ++id;
		}

		template<typename T>
		inline static int getTypeID()
		{
			static const int id = generateTypeID();
			return id;
		}

		template<typename T0, typename T1>
		inline static boolean sameType()
		{
			return getTypeID<T0>() == getTypeID<T1>();
		}
	}
}