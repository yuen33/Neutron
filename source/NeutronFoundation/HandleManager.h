#pragma once

#include "NeutronFoundationCommon.h"
#include "Array.h"

using Neutron::Container::Array;

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE Handle
		{
		protected:
			union
			{
				uint64 handle;
				struct
				{
					uint32 index;
					uint32 magic;
				};
			};

		public:
			Handle() : handle( 0 ) {}
			virtual ~Handle() {}

			operator uint64() const { return handle; }

			inline boolean isValid() const { return magic != 0; }
			inline uint64 getHandle() const { return handle; }
			inline uint32 getIndex() const { return index; }
			inline uint32 getMagic() const { return magic; }
		};

		template<typename T>
		class HandleConcrete : public Handle
		{
		public:
			HandleConcrete() {}
			HandleConcrete( const HandleConcrete& other ) { handle = other.handle; }
			HandleConcrete( uint64 value ) { handle = value; }
			HandleConcrete( uint32 index_, uint32 magic_ ) { index = index_; magic = magic_; }
			virtual ~HandleConcrete() {}

			HandleConcrete& operator=( const HandleConcrete& rhs ) { handle = rhs.handle; return *this; }
			HandleConcrete& operator=( uint64 value ) { handle = value; return *this; }
		};

		template<typename T, typename F>
		inline boolean operator==( const HandleConcrete<T>& lhs, const HandleConcrete<F>& rhs ) { return false; }
		template<typename T, typename F>
		inline boolean operator!=( const HandleConcrete<T>& lhs, const HandleConcrete<F>& rhs ) { return true; }
		template<typename T>
		inline boolean operator==( const HandleConcrete<T>& lhs, const HandleConcrete<T>& rhs ) { return lhs.getHandle() == rhs.getHandle(); }
		template<typename T>
		inline boolean operator!=( const HandleConcrete<T>& lhs, const HandleConcrete<T>& rhs ) { return lhs.getHandle() != rhs.getHandle(); }

		template<typename T>
		class HandleManager
		{	
			HandleManager() : magicCounter( 0 ) {}
			virtual ~HandleManager() {}

			static volatile uint32		magicCounter;
			static Array<uint32>		magics;
			static Array<uint32>		freeIndexes;
			static Array<T>				data;

		public:
			static HandleConcrete<T> acquire( const T& item )
			{
				HandleConcrete<T> h;
				if( !freeIndexes.empty() )
				{
					uint32 index = freeIndexes.back();
					h = HandleConcrete<T>( index, magics[index] );
					data[index] = item;
					freeIndexes.remove();
				}
				else
				{
					atomIncrement32( (int32*)&magicCounter );
					atomCAS32( &magicCounter, 1U, 0U );

					h = HandleConcrete<T>( data.getCount(), magicCounter );
					data.add( item );
					magics.add( h.magic );
				}

				return h;
			}

			static void release( const HandleConcrete<T>& handle )
			{
				if( isValid( handle ) )
				{
					freeIndexes.add( handle.index );
					data[handle.index] = (T)nullptr;
				}
			}

			static T deference( const HandleConcrete<T>& handle )
			{
				if( isValid( handle ) )
				{
					return data[handle.index];
				}
				return (T)0;
			}

			static boolean reuse( const HandleConcrete<T>& handle, const T& item )
			{
				if( isValid( handle ) )
				{
					data[handle.index] = item;
					return true;
				}
				return false;
			}

			static inline boolean isValid( const HandleConcrete<T>& handle )
			{
				return ( handle.isValid() && (int)handle.index < data.getCount() && handle.magic == magics[handle.index] );
			}

			static inline void clear()
			{
				magicCounter = 0;
				magics.clear();
				freeIndexes.clear();
				data.clear();
			}

			static inline const Array<T>& getData() { return data; }
		};

		template<typename T>
		volatile uint32 HandleManager<T>::magicCounter = 0;

		template<typename T>
		Array<uint32> HandleManager<T>::magics;

		template<typename T>
		Array<uint32> HandleManager<T>::freeIndexes;

		template<typename T>
		Array<T> HandleManager<T>::data;
	}
}