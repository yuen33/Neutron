#pragma once

#include "NeutronFoundationCommon.h"

namespace Neutron
{
	namespace Memory
	{
		class ListItem
		{
			ListItem* prev;
			ListItem* next;

		public:
			ListItem() : prev( 0 ), next( 0 ) {}
			virtual ~ListItem() {}

			inline void setPrev( ListItem* item ) { prev = item; }
			inline void setNext( ListItem* item ) { next = item; }
			inline ListItem* getPrev() { return prev; }
			inline ListItem* getNext() { return next; }
			inline const ListItem* getPrev() const { return prev; }
			inline const ListItem* getNext() const { return next; }
		};

		class NEUTRON_FOUNDATION_CORE List
		{
			ListItem* front;
			ListItem* back;
			int count;

		public:
			List() : front( 0 ), back( 0 ), count( 0 ) {}
			virtual ~List() {}

			ListItem* popFront()
			{
				if( front )
				{
					ListItem* ret = front;
					front = front->getNext();

					if( front )
					{
						front->setPrev( 0 );
					}
					else
					{
						back = 0;
					}

					--count;
					return ret;
				}

				return 0;
			}

			ListItem* popBack()
			{
				if( back )
				{
					ListItem* ret = back;
					back = back->getPrev();
					if( back )
					{
						back->setNext( 0 );
					}
					else
					{
						front = 0;
					}

					--count;
					return ret;
				}

				return 0;
			}

			void remove( ListItem* toRemove )
			{
				if( toRemove )
				{
					if( toRemove == front )
					{
						popFront();
					}
					else if( toRemove == back )
					{
						popBack();
					}
					else
					{
						toRemove->getPrev()->setNext( toRemove->getNext() );
						toRemove->getNext()->setPrev( toRemove->getPrev() );
						toRemove->setPrev( 0 );
						toRemove->setNext( 0 );
						--count;
					}
				}
			}

			void pushFront( ListItem* toInsert )
			{
				if( toInsert )
				{
					toInsert->setPrev( 0 );
					toInsert->setNext( front );
					if( front )
					{
						front->setPrev( toInsert );
					}
					else
					{
						back = toInsert;
					}
					front = toInsert;
					++count;
				}
			}

			void pushBack( ListItem* toInsert )
			{
				if( toInsert )
				{
					toInsert->setNext( 0 );
					toInsert->setPrev( back );
					if( back )
					{
						back->setNext( toInsert );
					}
					else
					{
						front = toInsert;
					}
					back = toInsert;
					++count;
				}
			}

			void insertBefore( ListItem* toInsert, ListItem* item )
			{
				if( toInsert && item )
				{
					toInsert->setNext( item );
					toInsert->setPrev( item->getPrev() );
					item->setPrev( toInsert );
					
					if( item == front )
					{
						front = toInsert;
					}
					else
					{
						item->getPrev()->setNext( toInsert );
					}
					++count;
				}
			}

			void insertAfter( ListItem* toInsert, ListItem* item )
			{
				if( toInsert && item )
				{
					toInsert->setPrev( item );
					toInsert->setNext( item->getNext() );
					item->setNext( toInsert );

					if( item == back )
					{
						back = toInsert;
					}
					else
					{
						item->getNext()->setPrev( toInsert );
					}
					++count;
				}
			}

			void clear()
			{
				front = 0;
				back = 0;
				count = 0;
			}

			inline ListItem* getFront() { return front; }
			inline ListItem* getBack() { return back; }
			inline int getCount() const { return count; }
			inline boolean empty() const { return count <= 0; }
			inline boolean any() const { return count > 0; }
		};
	}
}