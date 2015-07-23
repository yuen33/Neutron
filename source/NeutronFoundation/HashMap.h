#pragma once

#include "Array.h"

namespace Neutron
{
	namespace Container
	{
		template<typename Key, typename Value, typename CountType = int>
		class HashMap
		{
			enum : CountType
			{
				END_OF_LIST = 0x7fffffff
			};

			struct Entry
			{
				Key			key;
				CountType	next;
				Value		value;
			};

			struct FindResult
			{
				CountType	hash_i;
				CountType	data_i;
				CountType	data_prev;
			};

			Array<CountType>	hash;
			Array<Entry>		data;
			CountType			count;

			FindResult findEntry( Key key ) const
			{
				FindResult fr;
				fr.hash_i = END_OF_LIST;
				fr.data_i = END_OF_LIST;
				fr.data_prev = END_OF_LIST;

				if( !hash.empty() )
				{
					fr.hash_i = key % hash.getCount();
					fr.data_i = hash[fr.hash_i];
					while( fr.data_i != END_OF_LIST )
					{
						if( data[fr.data_i].key == key )
						{
							return fr;
						}

						fr.data_prev = fr.data_i;
						fr.data_i = data[fr.data_i].next;
					}
				}

				return fr;
			}

			CountType addEntry( const Key& key )
			{
				Entry e;
				e.key = key;
				e.next = END_OF_LIST;
				CountType ret = count;
				if( count < data.getCount() )
				{
					data[count] = e;
				}
				else
				{
					data.add( e );
				}
				++count;
				return ret;
			}

			void removeEntry( const FindResult& fr )
			{
				if( fr.data_prev == END_OF_LIST )
				{
					hash[fr.hash_i] = data[fr.data_i].next;
				}
				else
				{
					data[fr.data_prev].next = data[fr.data_i].next;
				}

				if( fr.data_i == count - 1 )
				{
					--count;
					return;
				}

				data[fr.data_i] = data[count - 1];
				--count;

				FindResult last = findEntry( data[fr.data_i].key );
				if( last.data_prev != END_OF_LIST )
				{
					data[last.data_prev].next = fr.data_i;
				}
				else
				{
					hash[last.hash_i] = fr.data_i;
				}
			}

			bool full()
			{
				static const float maxLoadFactor = 0.7f;
				return data.getCount() >= hash.getCount() * maxLoadFactor;
			}

			void grow()
			{
				CountType newCount = data.getCount() * 2 + 8;
				rehash( newCount );
			}

			void rehash( CountType newCount )
			{
				Array<CountType> oldHash( hash );
				Array<Entry> oldData( data );
				CountType oldCount = count;

				data.clear();
				hash.clear();

				hash.resize( newCount );
				data.reserve( oldCount );
				count = 0;

				for( CountType i = 0; i < newCount; ++i )
				{
					hash[i] = END_OF_LIST;
				}

				for( CountType i = 0; i < oldCount; ++i )
				{
					add( oldData[i].key, oldData[i].value );
				}
			}

			Entry* next( Entry* entry )
			{
				if( entry && entry >= data.begin() && entry < data.begin() + count - 1 )
				{
					return entry + 1;
				}

				return 0;
			}

		public:
			class Iterator
			{
				friend class HashMap < Key, Value, CountType > ;
				HashMap* owner;
				Entry* entry;

				Iterator( HashMap<Key, Value, CountType>* owner, Entry* entry )
					:owner( owner )
					, entry( entry )
				{
				}

			public:
				Iterator()
					:owner( 0 )
					, entry( 0 )
				{
				}

				Iterator( const Iterator& other )
					:owner( other.owner )
					, entry( other.entry )
				{
				}

				~Iterator()
				{
				}

				inline Iterator& operator=( const Iterator& rhs ) { owner = rhs.owner; entry = rhs.entry; return *this; }
				inline bool null() const { return !owner || !entry; }
				inline const Key& key() const { assert( entry ); return entry->key; }
				inline Key& key() { assert( entry ); return entry->key; }
				inline const Value& value() const { assert( entry ); return entry->value; }
				inline Value& value() { assert( entry ); return entry->value; }
				inline bool operator==( const Iterator& rhs ) const { return owner == rhs.owner && entry == rhs.entry; }
				inline bool operator!=( const Iterator& rhs ) const { return owner != rhs.owner || entry != rhs.entry; }
				inline Iterator& operator++( )
				{
					if( entry && owner )
					{
						entry = owner->next( entry );
					}
					return *this;
				}
				inline Iterator operator++( int )
				{
					Iterator it = *this;
					if( entry && owner )
					{
						entry = owner->next( entry );
					}
					return it;
				}
			};

			HashMap()
				:count( 0 )
			{
				grow();
			}

			virtual ~HashMap()
			{
			}

			void add( const Key& key, const Value& value )
			{
				FindResult fr = findEntry( key );
				if( fr.data_i != END_OF_LIST )
				{
					data[fr.data_i].value = value;
					return;
				}

				CountType i = addEntry( key );
				if( fr.data_prev == END_OF_LIST )
				{
					hash[fr.hash_i] = i;
				}
				else
				{
					data[fr.data_prev].next = i;
				}

				data[i].value = value;

				if( full() )
				{
					grow();
				}
			}

			void remove( const Key& key )
			{
				FindResult fr = findEntry( key );
				if( fr.data_i != END_OF_LIST )
				{
					removeEntry( fr );
				}
			}

			inline void remove( Iterator it )
			{
				remove( it.key() );
			}

			Iterator find( const Key& key )
			{
				FindResult fr = findEntry( key );
				if( fr.data_i != END_OF_LIST )
				{
					return Iterator( this, &data[fr.data_i] );
				}

				return end();
			}

			inline Iterator begin()
			{
				return count > 0 ? Iterator( this, data.begin() ) : end();
			}

			inline Iterator end()
			{
				return Iterator( this, 0 );
			}

			inline void reserve( CountType reserveCount )
			{
				rehash( reserveCount );
			}

			inline void clear()
			{
				data.clear();
				hash.clear();
				count = 0;
				grow();
			}

			inline CountType getCount() const { return count; }
		};
	}
}