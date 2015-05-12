#pragma once

#include "Array.h"

namespace Neutron
{
	namespace Container
	{
		template<typename T, typename CountType = int>
		class Stack : public Array<T, CountType>
		{
		public:
			Stack() {}
			~Stack() {}
			inline void push( const T& item ) { return add( item ); }
			inline void pop() { remove(); }
			inline T& peek() { return back(); }
			inline const T& peek() const { return back(); }
		};
	}
}