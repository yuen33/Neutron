#pragma once

#include "Platform.h"
#include "Hash.h"

namespace Neutron
{
	namespace Utility
	{
		template<uint32 N, uint32 I = 0>
		struct CompileHashOperator
		{
			static const uint32 apply( const char(&s)[N] )
			{
				return ( ( CompileHashOperator<N, I+1>::apply( s ) << 5L ) + CompileHashOperator<N, I+1>::apply( s ) ) + s[I];
			}
		};

		template<uint32 N>
		struct CompileHashOperator<N, N>
		{
			static const uint32 apply( const char(&s)[N] )
			{
				return 5381U;
			}
		};

		template<uint32 N>
		const uint32 CompileHashDJB( const char(&s)[N] )
		{
			return Math::Hash::DJB32( s );
			//return CompileHashOperator<N>::apply( s );
		}

		/*template<uint32 N, uint32 I = 0>
		struct hash_calc
		{
			static const uint32 apply( const char(&s)[N] )
			{
				return ( hash_calc<N, I+1>::apply( s ) << 5L + hash_calc<N, I+1>::apply( s ) ) + s[I];
			}
		};

		template<uint32 N>
		struct hash_calc<N, N>
		{
			static const uint32 apply( const char( &s )[N] )
			{
				return 5381U;
			}
		};

		template<uint32 N>
		const uint32 string_hash( const char (&s)[N] )
		{
			return hash_calc<N>::apply( s );
		};

		static const uint32 string_hash( const char* s )
		{
			uint32 hash = 5381U;
			while( *s )
			{
				hash = ( ( hash << 5L ) + hash ) + *s;
				++s;
			}

			return hash;
		}*/

#define STRING( s ) #s
#define STRINGFY( s ) STRING( s )
#define STRING_STUB( prefix, s ) _STRING_STUB_##prefix_##s
#define CREATE_STRING_STUB( prefix, s ) static const uint32 STRING_STUB( prefix, s ) = Neutron::Utility::CompileHashDJB( STRINGFY( s ) )
#define COMPARE_STRING_STUB( v, s ) ( ( v ) == STRING_STUB( s ) )
	}
}