#pragma once

#include "Buffer.h"

namespace Neutron
{
	namespace Container
	{
		template<typename T, typename CountType = int>
		class Array : public Buffer<T>
		{
		public:
			Array()
			{
			}

			Array( const T* data, CountType count )
				:Buffer( data, count )
			{
			}

			Array( const Array& other )
				:Buffer( other )
			{
			}

			~Array()
			{
			}

			Array& operator=( const Array& rhs )
			{
				Buffer::operator=( rhs );
				return *this;
			}

			inline T& operator[]( CountType index ) { assert( index < count && index >= 0 ); return data[index]; }
			inline const T& operator[]( CountType index ) const { assert( index < count && index >= 0 ); return data[index]; }
			inline T& front() { return data[0]; }
			inline T& back() { return data[count-1]; }
			inline const T& front() const { return data[0]; }
			inline const T& back() const { return data[count-1]; }

			inline void add( const T& item )
			{
				if( count + 1 > capacity )
				{
					grow();
				}

				data[count++] = item;
			}

			inline void add( const Array<T>& other )
			{
				reserve( count + other.count );
				for( CountType i = 0; i < other.count; ++i )
				{
					data[count++] = other[i];
				}
			}

			inline void remove()
			{
				--count;
			}

			inline void removeAt( CountType index )
			{
				assert( index < count && index >= 0 );				
				for( CountType i = index + 1; i < count; ++i )
				{
					data[i-1] = data[i];
				}
				--count;
			}

			inline void removeAtFast( CountType index )
			{
				assert( index < count && index >= 0 );
				data[index] = data[count-1];
				--count;
			}

			inline T* begin() { return &data[0]; }
			inline T* end() { return 0; }
		};
	}
}