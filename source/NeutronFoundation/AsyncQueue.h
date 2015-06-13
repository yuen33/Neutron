#pragma once

#include "Array.h"

using Neutron::Container::Array;

namespace Neutron
{
	namespace Container
	{
		template<typename T, typename CountType = int>
		class AsyncQueue
		{
			Array<T>			data;
			CountType			pushIndex;
			CountType			popIndex;
			CountType			maxPopIndex;
			CountType			capacity;
			volatile CountType	count;

		public:
			AsyncQueue()
				:pushIndex( 0 )
				,popIndex( 0 )
				,maxPopIndex( 0 )
				,capacity( 0 )
				,count( 0 )
			{
			}

			AsyncQueue( CountType newCapacity )
				:pushIndex( 0 )
				,popIndex( 0 )
				,maxPopIndex( 0 )
				,capacity( 0 )
				,count( 0 )
			{
				reserve( newCapacity )
			}

			virtual ~AsyncQueue()
			{
			}

			void reserve( CountType newCapacity )
			{
				data.resize( newCapacity + 1 );
				capacity = data.getCount();
			}

			inline CountType getCount() const { return count; }
			inline boolean any() const { return count > 0; }
			inline boolean empty() const { return count == 0; }

			boolean push( const T& item )
			{
				CountType tempPopIndex = 0;
				CountType tempPushIndex = 0;

				// try next space
				do
				{
					tempPushIndex = pushIndex;
					tempPopIndex = popIndex;
					if( ( tempPushIndex + 1 ) % capacity == tempPopIndex % capacity )
					{
						// full
						return false;
					}
				}while( !atomCAS32( (uint32*)&pushIndex, ( tempPushIndex + 1 ), tempPushIndex ) );

				// commit
				data[tempPushIndex % capacity] = item;

				// set max pop counter
				while( !atomCAS32( (uint32*)&maxPopIndex, ( tempPushIndex + 1 ), tempPushIndex ) )
				{
					yield();
				}

				// update count
				atomIncrement32( &count );

				return true;
			}

			boolean pop( T& item )
			{
				CountType tempMaxPopIndex;
				CountType tempPopIndex;

				do
				{
					tempPopIndex = popIndex;
					tempMaxPopIndex = maxPopIndex;
					if( tempPopIndex % capacity == maxPopIndex % capacity )
					{
						// empty or producer has the space but not commit
						return false;
					}

					// fetch
					item = data[tempPopIndex % capacity];

					// set pop counter
					if( atomCAS32( (uint32*)&popIndex, ( tempPopIndex + 1 ), tempPopIndex ) )
					{
						atomDecrement32( &count );
						return true;
					}
				}while( true );

				// should NOT reach here!
				assert( 0 );
				return false;
			}

			inline boolean pop()
			{
				CountType tempMaxPopIndex;
				CountType tempPopIndex;

				do
				{
					tempPopIndex = popIndex;
					tempMaxPopIndex = maxPopIndex;
					if( tempPopIndex % capacity == maxPopIndex % capacity )
					{
						// empty or producer has the space but not commit
						return false;
					}

					// fetch
					//item = data[tempPopIndex % capacity];

					// set pop counter
					if( atomCAS32( (uint32*)&popIndex, ( tempPopIndex + 1 ), tempPopIndex ) )
					{
						atomDecrement32( &count );
						return true;
					}
				}while( true );

				// should NOT reach here!
				assert( 0 );
				return false;
			}

			const T& peek() const
			{
				return data[popIndex % capacity];
			}
		};
	}
}