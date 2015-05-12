#pragma once

#include "Platform.h"

namespace Neutron
{
	namespace Container
	{
		template<typename T, typename CountType = int>
		class Buffer
		{
		public:
			typedef CountType IndexType;
			typedef T ValueType;

		protected:
			CountType		count;
			CountType		capacity;
			T*				data;

			inline void cleanup()
			{
				clear();
				shrink();
			}

			void setCapacity( CountType newCapacity )
			{
				if( newCapacity == capacity )
				{
					return;
				}

				if( newCapacity < count )
				{
					resize( newCapacity );
				}

				T* newData = 0;
				if( newCapacity > 0 )
				{
					newData = new T[newCapacity];
					assert( newData );
					for( CountType i = 0; i < count; ++i )
					{
						newData[i] = data[i];
					}
				}

				delete [] data;
				data = newData;
				capacity = newCapacity;
			}

			inline void copy( T* data, CountType count )
			{
				reserve( count );
				for( CountType i = 0; i < count; ++i )
				{
					this->data[i] = data[i];
				}

				this->count = count;
			}

		public:
			Buffer()
				:capacity( 0 )
				,count( 0 )
				,data( 0 )
			{
				reserve( count );
			}

			Buffer( CountType capacaity )
				:capacity( 0 )
				,count( 0 )
				,data( 0 )
			{
				reserve( capacity );
			}

			Buffer( const T* data, CountType count )
				:capacity( 0 )
				,count( 0 )
				,data( 0 )
			{
				copy( data, count );
			}

			Buffer( const Buffer& other )
				:capacity( 0 )
				,count( 0 )
				,data( 0 )
			{
				copy( other.data, other.count );
			}

			virtual ~Buffer()
			{
				cleanup();
			}

			inline Buffer& operator=( const Buffer& rhs )
			{
				reserve( rhs.count );
				copy( rhs.data, rhs.count );
				return *this;
			}

			inline void copy( const T* data, CountType size )
			{
				reserve( rhs.count );
				copy( data, size );
			}

			inline void grow( CountType newCapacity = 0 )
			{
				CountType estimateCapacity = capacity * 2 + 8;
				setCapacity( newCapacity > estimateCapacity ? newCapacity : estimateCapacity );
			}

			inline void resize( CountType newCount )
			{
				if( newCount > capacity )
				{
					grow( newCount );
				}

				count = newCount;
			}

			inline void reserve( CountType newCapacity )
			{
				if( newCapacity > capacity )
				{
					setCapacity( newCapacity );
				}
			}

			inline void clear() { count = 0; }
			inline void shrink() { setCapacity( count ); }
			inline CountType getCount() const { return count; }
			inline CountType getCapacity() const { return capacity; }
			inline boolean empty() const { return count == 0; }
			inline boolean any() const { return count > 0; }
			inline T* getData() { return data; }
			inline const T* getData() const { return data; }
		};
	}
}