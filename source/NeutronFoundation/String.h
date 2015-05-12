#pragma once

#include "Array.h"
#include "Type.h"

namespace Neutron
{
	namespace Container
	{
		template<typename CharType = char, typename CountType = int>
		class String_T : public Array < CharType, CountType >
		{
			void grow( CountType newCapacity )
			{
				Array<CharType, CountType>::grow( newCapacity );
				data[count] = 0;
			}

		public:
			String_T()
			{
			}

			String_T( const CharType* str )
			{
				insert( 0, str );
			}

			String_T( const String_T& other )
			{
				insert( 0, other );
			}

			virtual ~String_T()
			{
				cleanup();
			}

			inline String_T& operator=( const CharType s ) { insert( 0, c ); return *this; }
			inline String_T& operator=( const CharType* s ) { insert( 0, s ); return *this; }
			inline String_T& operator=( const String_T& s ) { insert( 0, s ); return *this; }
			inline String_T operator+( const CharType c ) const { String temp = *this; temp.insert( count, c ); return temp; }
			inline String_T operator+( const CharType* s ) const { String temp = *this; temp.insert( count, s ); return temp; }
			inline String_T operator+( const String_T& s ) const { String temp = *this; temp.insert( count, s ); return temp; }
			inline String_T& operator+=( const CharType c ) { insert( count, c ); return *this; }
			inline String_T& operator+=( const CharType* s ) { insert( count, s ); return *this; }
			inline String_T& operator+=( const String_T& s ) { insert( count, s ); return *this; }

			static int compare( const String_T& lhs, const String_T& rhs )
			{
				for( CountType i = 0; i < lhs.count && i < rhs.count; ++i )
				{
					int ret = lhs[i] - rhs[i];
					if( ret != 0 )
					{
						return ret < 0 ? -1 : 1;
					}
				}

				if( lhs.count == rhs.count )
				{
					return 0;
				}
				else
				{
					return lhs.count < rhs.count ? -1 : 1;
				}
			}

			String_T& insert( CountType pos, CharType c )
			{
				assert( pos >= 0 && pos <= count && c != 0 );
				if( pos >= 0 && pos <= count )
				{
					// prepare buffer
					if( count + 2 > capacity )
					{
						grow( count + 2 );
					}

					// move sub string
					memcpy( data + pos + 1, data + pos, count - pos );

					// insert 
					data[pos] = c;

					// update count
					count += 1;

					// ensure end character
					data[count] = 0;
				}

				return *this;
			}

			String_T& insert( CountType pos, const CharType* src, CountType srcPos = 0, CountType srcCount = 0 )
			{
				assert( pos >= 0 && pos <= count && src && srcPos >= 0 );
				if( pos >= 0 && pos <= count && src && srcPos >= 0 )
				{
					// get source string length
					if( srcCount == 0 )
					{
						srcCount = getCStrCount( src );
					}

					if( srcCount > 0 )
					{
						// prepare buffer
						if( count + srcCount + 1 > capacity )
						{
							grow( count + srcCount + 1 );
						}

						// move sub string
						if( pos > 0 )
						{
							memcpy( data + pos + srcCount, data + pos, count - pos );
						}

						// insert
						memcpy( data + pos, src + srcPos, srcCount );

						// update count
						count += srcCount;

						// ensure end character
						data[count] = 0;
					}
				}

				return *this;
			}

			String_T& insert( CountType pos, const String_T& src, CountType srcPos = 0, CountType srcCount = 0 )
			{
				assert( pos >= 0 && pos <= count && srcPos >= 0 && srcCount >= 0 );
				if( pos >= 0 && pos <= count && srcPos >= 0 )
				{
					if( src.any() )
					{
						// get source string length
						if( srcCount == 0 )
						{
							srcCount = src.count;
						}

						if( srcCount > 0 )
						{
							// prepare buffer
							if( count + srcCount + 1 > capacity )
							{
								grow( count + srcCount + 1 );
							}

							// move sub string
							if( pos > 0 )
							{
								memcpy( data + pos + srcCount, data + pos, count - pos );
							}

							// insert
							memcpy( data + pos, src.data + srcPos, srcCount );
							// update count
							count += srcCount;
							// ensure end character
							data[count] = 0;
						}
					}
				}

				return *this;
			}

			String_T& remove()
			{
				remove( count - 1, 1 );
				return *this;
			}

			String_T& remove( CountType pos, CountType removeCount = 0 )
			{
				if( count > 0 )
				{
					// get remove count
					if( removeCount == 0 )
					{
						removeCount = count - pos;
					}

					if( pos + removeCount <= count )
					{
						// move sub string
						memcpy( data + pos, data + pos + removeCount, count - pos - removeCount );
						// update count
						count -= removeCount;
						// ensure end character
						data[count] = 0;
					}
				}

				return *this;
			}

			void clear()
			{
				if( count > 0 )
				{
					Array::clear();
					data[0] = 0;
				}
			}

			int find( const CharType c ) const
			{
				if( count > 0 )
				{
					for( CountType i = 0; i < count; ++i )
					{
						if( data[i] == c )
						{
							return i;
						}
					}
				}
				return -1;
			}

			int find( const CharType* str ) const
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					CountType len = getCStrCount( str );
					for( CountType i = 0; i < count; ++i )
					{
						if( !strncmp( data + i, str, len ) )
						{
							return i;
						}
					}
				}

				return -1;
			}

			int find( const String_T& str ) const
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					for( CountType i = 0; i < count; ++i )
					{
						if( !strncmp( data + i, str, str.getCount() ) )
						{
							return i;
						}
					}
				}

				return -1;
			}

			int rfind( const CharType c ) const
			{
				if( count > 0 )
				{
					for( CountType i = count - 1; i >= 0; --i )
					{
						if( data[i] == c )
						{
							return i;
						}
					}
				}

				return -1;
			}

			int rfind( const CharType* str ) const
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					CountType len = getCStrCount( str );
					for( CountType i = count - 1; i >= 0; --i )
					{
						if( !strncmp( data + i, str, len ) )
						{
							return i;
						}
					}
				}

				return -1;
			}

			int rfind( const String_T& str ) const
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					for( CountType i = count - 1; i >= 0; --i )
					{
						if( !strncmp( data + i, str.data, str.count ) )
						{
							return i;
						}
					}
				}

				return -1;
			}

			String_T& lower()
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					char* s = data;
					while( *s )
					{
						char c = *s;
						if( c >= 'a' && c <= 'z' )
						{
							*s += ( 'a' - 'A' );
						}
						++s;
					}
				}

				return *this;
			}

			String_T& upper()
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					char* s = data;
					while( *s )
					{
						char c = *s;
						if( c >= 'a' && c <= 'z' )
						{
							*s -= ( 'a' - 'A' );
						}
						++s;
					}
				}

				return *this;
			}

			String_T& trim( const CharType* symbols = 0 )
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					if( !symbols )
					{
						symbols = " ";
					}

					const char* left = data;
					while( *left && strchr( symbols, *left ) != 0 )
					{
						++left;
					}

					const char* right = data + count - 1;
					while( *right && strchr( symbols, *right ) != 0 )
					{
						--right;
					}
					++right;

					if( right > left )
					{
						memcpy( data, left, right - left );
						count = (CountType)( right - left );
						data[count] = 0;
					}
					else
					{
						clear();
					}
				}

				return *this;
			}

			String_T& replace( const char* before, const char* after )
			{
				if( count > 0 && Type::sameType<CharType, char>() )
				{
					String_T res;
					char* s = data;
					CountType len = getCStrCount( before );

					while( *s )
					{
						if( !strncmp( s, before, len ) )
						{
							res += after;
							s += len;
						}
						else
						{
							res += *s;
							//res.add( *s );
							++s;
						}
					}

					*this = res;
				}

				return *this;
			}

			static String_T format( const char* format, ... )
			{
				String_T ret;
				if( Type::sameType<CharType, char>() )
				{
					char* buffer = new char[1024];
					va_list arg_list;
					va_start( arg_list, format );
					vsprintf_s( buffer, 1024, format, arg_list );
					va_end( arg_list );
					ret = buffer;
					delete[] buffer;
				}

				return ret;
			}

			String_T& subString( Size pos, Size subStringCount ) const
			{
				assert( pos + subStringCount <= count );
				String_T dest;
				dest.insert( 0, *this, pos, subStringCount );
				return dest;
			}

			static void split( const String_T& srcString, Array<String_T>& subStrings, const CharType* delimiters = " ,\t\n" )
			{
				String_T temp = srcString;
				if( temp.count > 0 && Type::sameType<CharType, char>() )
				{
					char* nextToken = 0;
					char* token = strtok_s( temp.data, delimiters, &nextToken );
					while( token )
					{
						subStrings.add( String_T( token ) );
						token = strtok_s( 0, delimiters, &nextToken );
					}
				}
			}

			static String_T merge( Array<String_T>& subStrings, const char delimiter )
			{
				String temp;

				CountType newCount = 0;
				for( Array::IndexType i = 0; i < subStrings.getCount(); ++i )
				{
					newCount += subStrings[i].getCount();
				}

				newCount += subStrings.getCount() - 1;

				temp.reserve( newCount );

				for( Array<String_T>::IndexType i = 0; i < subStrings.getCount(); ++i )
				{
					temp.add( subStrings[i] );
					temp.add( delimiter );
				}

				temp.remove();

				return temp;
			}

			inline CharType* getCStr( CountType offset = 0 ) const
			{
				return data && offset < count ? data + offset : "";
				//return data ? data : "";
			}

			inline CountType getCapacity() const
			{
				return capacity - 1;
			}

			inline static CountType getCStrCount( const CharType* str )
			{
				if( str )
				{
					CountType len = 0;
					CharType c = str[len];
					while( c != 0 ) c = str[len++];
					return len - 1;
				}
				return 0;
			}
		};

		template<typename CharType = char, typename CountType = int>
		static bool operator==( const String_T<CharType, CountType>& lhs, const String_T<CharType, CountType>& rhs )
		{
			return lhs.getCount() == rhs.getCount() && String_T<CharType, CountType>::compare( lhs, rhs ) == 0;
		}

		template<typename CharType = char, typename CountType = int>
		static bool operator!=( const String_T<CharType, CountType>& lhs, const String_T<CharType, CountType>& rhs )
		{
			return lhs.getCount() != rhs.getCount() && String_T<CharType, CountType>::compare( lhs, rhs ) != 0;
		}

		typedef String_T<char, int> String;
	}
}