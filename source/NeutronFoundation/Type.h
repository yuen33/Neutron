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
		inline static const int getTypeID()
		{
			static const int id = generateTypeID();
			return id;
		}

		template<typename T0, typename T1>
		inline static const boolean sameType()
		{
			return getTypeID<T0>() == getTypeID<T1>();
		}
	}
}