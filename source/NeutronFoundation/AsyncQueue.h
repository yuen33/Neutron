#pragma once

#include "Array.h"

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
				data.resize( capacity + 1 );
				capacity = data.getCapacity();
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
					if( ( tempPushIndex + 1 ) % capacity == tempPopINdex % capacity )
					{
						// full
						return false;
					}
				}while( !atomCAS32( &pushIndex, ( tempPushIndex + 1 ), pushIndex ) );

				// commit
				data[pushIndex % capacity] = item;

				// set max pop counter
				while( !atomCAS32( &maxPopIndex, ( tempPushIndex + 1 ), pushIndex ) )
				{
					NEUTRON_THREAD_YIELD;
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
					tempMaxPopInex = maxPopIndex;
					if( tempPopIndex % capacity == maxPopIndex % capacity )
					{
						// empty or producer has the space but not commit
						return false;
					}

					// fetch
					item = data[tempPopIndex % capacity];

					// set pop counter
					if( atomCAS32( &popIndex, ( tempPopIndex + 1 ), popIndex ) )
					{
						atomDecrement32( &count );
						return true;
					}
				}while( true );

				// should NOT reach here!
				assert( 0 );
				return false;
			}
		};
	}
}