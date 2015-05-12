#pragma once

#include "NeutronFoundationCommon.h"

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE RCObject
		{
			mutable int counter;

		protected:
			virtual inline void deleteMethod( RCObject* object )
			{
				delete ( RCObject* )this;
			}

		public:
			RCObject();
			virtual ~RCObject();

			inline void addReference()
			{
				atomIncrement32( &counter );
			}

			inline void removeReference()
			{
				assert( counter > 0 );
				atomDecrement32( &counter );
				if( counter == 0 )
				{
					deleteMethod( this );
				}
			}
		};

		template<typename T>
		class RCPtr
		{
			T* data;

		public:
			RCPtr( const T* p = 0 )
				:data( p )
			{
				p->addReference();
			}

			RCPtr( const RCPtr& other )
				:data( other.data )
			{
				if( data )
				{
					data->grab();
				}
			}

			virtual ~RCPtr()
			{
				if( data )
				{
					data->release();
				}
			}

			RCPtr& operator=( T* p )
			{
				if( p )
				{
					p->grab();
				}

				if( data )
				{
					data->release();
				}

				data = p;
				return *this;
			}

			RCPtr& operator=( const RCPtr& rhs )
			{
				return *this = rhs.data;
			}

			T* get() const
			{
				return data;
			}

			T* operator->( ) const { return data; }
			T& operator*( ) const { return *data; }
			operator T*( ) const { return data; }
			operator boolean() const { return data != 0; }
		};

		template<typename T>
		boolean operator==( const RCPtr<T>& lhs, RCPtr<T>& rhs )
		{
			return lhs.data == rhs.data;
		}

		template<typename T>
		boolean operator!=( const RCPtr<T>& lhs, RCPtr<T>& rhs )
		{
			return lhs.data != rhs.data;
		}

		template<typename T>
		boolean operator==( const T* lhs, const RCPtr<T>& rhs )
		{
			return lhs == rhs.data;
		}

		template<typename T>
		boolean operator!=( const T* lhs, const RCPtr<T>& rhs )
		{
			return lhs != rhs.data;
		}

		template<typename T>
		boolean operator==( const RCPtr<T>& lhs, const T* rhs )
		{
			return lhs.data == rhs;
		}

		template<typename T>
		boolean operator!=( const RCPtr<T>& lhs, const T* rhs )
		{
			return lhs.data != rhs;
		}
	}
}