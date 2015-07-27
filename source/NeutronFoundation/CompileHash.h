#pragma once

#include "Platform.h"

namespace Neutron
{
	namespace Utility
	{
		template<uint32 N, uint32 I = 0>
		struct CompileHashOperator
		{
			static const uint32 apply( const char(&s)[N] )
			{
				return ( CompileHashOperator<N, I+1>::apply( s ) << 5L + CompileHashOperator<N, I+1>::apply( s ) ) + s[I];
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
			return CompileHashOperator<N>::apply( s );
		}

#define STRING( s ) #s
#define STRINGFY( s ) STRING( s )
#define STRING_STUB( s ) _STRING_STUB_##s
#define CREATE_STRING_STUB static const uint32 STRING_STUB( s ) = Neutron::Utility::CompileHashDJB( STRINGFY( s ) )
#define COMPARE_STRING_STUB( v, s ) ( v == STRING_STUB( s ) )
	}
}