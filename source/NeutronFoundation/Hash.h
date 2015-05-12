#pragma once

#include "Platform.h"

namespace Neutron
{
	namespace Math
	{
		class Hash
		{
		public:
			static inline uint32 DJB32( const char* p )
			{
				uint32 h = 5381;
				while( *p )
				{
					h += ( h << 5 ) + ( *p++ );
				}

				return h & 0x7fffffff;
			}

			static inline uint32 DJB32( const char* p, uint32 size )
			{
				uint32 h = 5381;
				while( size )
				{
					h += ( h << 5 ) + ( *p++ );
					--size;
				}

				return h & 0x7fffffff;
			}

			template<typename T>
			static inline uint32 hash( const T& val )
			{
				const int size_t_bits = sizeof( uint32 ) * 8;
				const int length = ( sizeof( T ) * 8 - 1 ) / size_t_bits;

				Neutron::Size seed = 0;

				for( unsigned int i = length * size_t_bits; i > 0; i -= size_t_bits )
				{
					seed ^= (uint32)( val >> i ) + ( seed << 6 ) + ( seed >> 2 );
				}
				seed ^= (uint32)val + ( seed << 6 ) + ( seed >> 2 );

				return seed;
			}

			template<typename T>
			static inline void combine( uint32& seed, const T& v )
			{
				seed ^= hash_value( v ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
			}

			template <class It>
			static inline uint32 range( It first, It last )
			{
				uint32 seed = 0;

				for( ; first != last; ++first )
				{
					hash_combine( seed, *first );
				}

				return seed;
			}

			template <class It>
			static inline void range( uint32& seed, It first, It last )
			{
				for( ; first != last; ++first )
				{
					hash_combine( seed, *first );
				}
			}
		};
	}
}