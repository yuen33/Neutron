#pragma once

#include "Platform.h"

namespace Neutron
{
	namespace Math
	{
		class Hash
		{
		public:
			inline static const uint32 DJB32( const char* p )
			{
				uint32 h = 5381U;
				while( *p )
				{
					h = ( ( h << 5L ) + h ) + *p;
					++p;
				}

				/*while( *p )
				{
					h = ( h << 5L ) + h + *p;
					++p;
				}*/

				return h;
			}

			inline static const uint32 DJB32( const char* p, uint32 size )
			{
				uint32 h = 5381U;
				while( size )
				{
					h = ( h << 5L ) + h + ( *p );
					++p;
					--size;
				}

				return h;
			}

			template<typename T>
			inline static const uint32 hash( const T& val )
			{
				const int size_t_bits = sizeof( uint32 ) * 8;
				const int length = ( sizeof( T ) * 8 - 1 ) / size_t_bits;

				uint32 seed = 0;

				for( unsigned int i = length * size_t_bits; i > 0; i -= size_t_bits )
				{
					seed ^= (uint32)( val >> i ) + ( seed << 6 ) + ( seed >> 2 );
				}
				seed ^= (uint32)val + ( seed << 6 ) + ( seed >> 2 );

				return seed;
			}

			template<typename T>
			inline static void combine( uint32& seed, const T& v )
			{
				seed ^= hash( v ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
			}

			template <class It>
			inline static const uint32 range( It first, It last )
			{
				uint32 seed = 0;

				for( ; first != last; ++first )
				{
					combine( seed, *first );
				}

				return seed;
			}

			template <class It>
			inline static const void range( uint32& seed, It first, It last )
			{
				for( ; first != last; ++first )
				{
					combine( seed, *first );
				}
			}
		};
	}
}