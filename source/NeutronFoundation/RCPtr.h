#pragma once

#include "NeutronFoundationCommon.h"

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE RCObject
		{
			volatile int32 counter;

		protected:
			virtual inline void deleteMethod( RCObject* object )
			{
				delete ( RCObject* )this;
			}

		public:
			RCObject() : counter( 0 ) {}
			virtual ~RCObject() {}

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

			inline int32 getReferenceCount() { return counter; }
		};

		template<typename T>
		class RCPtr
		{
			T* data;

		public:
			RCPtr()
				: data( 0 )
			{
			}

			RCPtr( T* p )
				: data( p )
			{
				if( data )
				{
					data->addReference();
				}
			}

			RCPtr( const RCPtr& other )
				: data( other.data )
			{
				if( data )
				{
					data->addReference();
				}
			}

			virtual ~RCPtr()
			{
				if( data )
				{
					data->removeReference();
				}
			}

			RCPtr& operator=( T* p )
			{
				if( p )
				{
					p->addReference();
				}

				if( data )
				{
					data->removeReference();
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
			boolean isNull() const { return data == 0; }
			static RCPtr<T> null;
		};

		template<typename T>
		RCPtr<T> RCPtr<T>::null = RCPtr<T>();

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

		template<typename T, typename U>
		RCPtr<T> dynamicCast( const RCPtr<U> p )
		{
			T* r = dynamic_cast<T*>( p.get() );
			return r != 0 ? RCPtr<T>( r ) : RCPtr<T>();
		}

		template<typename T, typename U>
		RCPtr<T> staticCast( const RCPtr<U> p )
		{
			T* r = static_cast<T*>( p.get() );
			return r != 0 ? RCPtr<T>( r ) : RCPtr<T>();
		}

		template<typename T, typename U>
		RCPtr<T> reinterpretCast( const RCPtr<U> p )
		{
			T* r = reinterpret_cast<T*>( p.get() );
			return RCPtr<T>( r );
		}
	}
}