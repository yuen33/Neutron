#include "FileJson.h"
#include "IOInterface.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"

using Neutron::Utility::IOStdFile;

namespace Neutron
{
	namespace Utility
	{
		FileJson::FileJson()
		{
		}

		FileJson::~FileJson()
		{
		}

		boolean FileJson::load( Document& jdoc, const char* path )
		{
			// open file
			IOStdFile* file = new IOStdFile( path, "rb" );
			assert( file );
			if( file )
			{
				// read data
				Size fileSize = file->getSize();
				char* data = new char[fileSize + 1];
				memset( data, 0, fileSize );
				assert( data );
				data[fileSize] = '\0';
				file->read( (uint8*)data, fileSize );
				delete file;
				file = 0;

				// parse data
				jdoc.Parse( data );
				delete [] data;
				data = 0;

				if( !jdoc.HasParseError() )
				{
					return true;
				}

				printf( "parse file %s error: %s\n", path, getErrorMessage( jdoc ) );
				return false;
			}

			printf( "open file %s failed\n", path );
			return false;
		}

		void FileJson::save( const Document& jdoc, const char* path )
		{
			if( !jdoc.HasParseError() )
			{
				rapidjson::StringBuffer buffer;
				rapidjson::PrettyWriter<rapidjson::StringBuffer> writer( buffer );
				jdoc.Accept( writer );

				IOStdFile* file = new IOStdFile( path, "wb" );
				assert( file );
				file->write( (uint8*)buffer.GetString(), buffer.GetSize() );
				delete file;
				file = 0;
			}
		}

		const char* FileJson:: getErrorMessage( const Document& jdoc )
		{
			return rapidjson::GetParseError_En( jdoc.GetParseError() );
		}

		boolean FileJson::tryRead( const Value& v, boolean& ret )
		{
			if( v.IsBool() )
			{
				ret = v.GetBool();
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, int32& ret )
		{
			if( v.IsInt() )
			{
				ret = v.GetInt();
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, int64& ret )
		{
			if( v.IsInt64() )
			{
				ret = v.GetInt64();
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, uint32& ret )
		{
			if( v.IsUint() )
			{
				ret = v.GetUint();
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, uint64& ret )
		{
			if( v.IsUint64() )
			{
				ret = v.GetUint64();
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, float& ret )
		{
			if( v.IsDouble() )
			{
				ret = static_cast<float>( v.GetDouble() );
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, float2& ret )
		{
			if( v.IsArray() && v.Size() == 2 && v[0].IsDouble() )
			{
				ret.x = static_cast<float>( v[0].GetDouble() );
				ret.y = static_cast<float>( v[1].GetDouble() );
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, float3& ret )
		{
			if( v.IsArray() && v.Size() == 3 && v[0].IsDouble() )
			{
				ret.x = static_cast<float>( v[0].GetDouble() );
				ret.y = static_cast<float>( v[1].GetDouble() );
				ret.z = static_cast<float>( v[2].GetDouble() );
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, float4& ret )
		{
			if( v.IsArray() && v.Size() == 4 && v[0].IsDouble() )
			{
				ret.x = static_cast<float>( v[0].GetDouble() );
				ret.y = static_cast<float>( v[1].GetDouble() );
				ret.z = static_cast<float>( v[2].GetDouble() );
				ret.w = static_cast<float>( v[3].GetDouble() );
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, float4x4& ret )
		{
			if( v.IsArray() && v.Size() == 16 && v[0].IsDouble() )
			{
				for( int i = 0; i < 16; ++i )
				{
					ret[i] = static_cast<float>( v[i].GetDouble() );
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, double& ret )
		{
			if( v.IsDouble() )
			{
				ret = v.GetDouble();
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, String& ret )
		{
			if( v.IsString() )
			{
				ret = v.GetString();
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<boolean>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsBool() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = v[i].GetBool();
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<int32>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsInt() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = v[i].GetInt();
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<int64>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsInt64() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = v[i].GetInt64();
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<uint32>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsUint() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = v[i].GetUint();
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<uint64>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsUint64() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = v[i].GetUint64();
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<float>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsDouble() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = static_cast<float>( v[i].GetDouble() );
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<double>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsDouble() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = v[i].GetDouble();
				}
				return true;
			}
			return false;
		}

		boolean FileJson::tryRead( const Value& v, Array<String>& ret )
		{
			if( v.IsArray() && v[(SizeType)0].IsString() )
			{
				ret.resize( v.Size() );
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret[i] = v[i].GetString();
				}
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, const boolean& defaultValue )
		{
			return v.IsBool() ? v.GetBool() : defaultValue;
		}

		int32 FileJson::read( const Value& v, const int32& defaultValue )
		{
			return v.IsInt() ? v.GetInt() : defaultValue;
		}

		int64 FileJson::read( const Value& v, const int64& defaultValue )
		{
			return v.IsInt64() ? v.GetInt64() : defaultValue;
		}

		uint32 FileJson::read( const Value& v, const uint32& defaultValue )
		{
			return v.IsUint() ? v.GetUint() : defaultValue;
		}

		uint64 FileJson::read( const Value& v, const uint64& defaultValue )
		{
			return v.IsUint64() ? v.GetUint64() : defaultValue;
		}

		float FileJson::read( const Value& v, const float& defaultValue )
		{
			return v.IsDouble() ? static_cast<float>( v.GetDouble() ) : defaultValue;
		}

		float2 FileJson::read( const Value& v, const float2& defaultValue )
		{
			return ( v.IsArray() && v.Size() == 2 && v[0].IsDouble() ) ? float2( static_cast<float>( v[0].GetDouble() ), static_cast<float>( v[1].GetDouble() ) ) : defaultValue;
		}

		float3 FileJson::read( const Value& v, const float3& defaultValue )
		{
			return ( v.IsArray() && v.Size() == 3 && v[0].IsDouble() ) ? float3( static_cast<float>( v[0].GetDouble() ), static_cast<float>( v[1].GetDouble() ), static_cast<float>( v[2].GetDouble() ) ) : defaultValue;
		}

		float4 FileJson::read( const Value& v, const float4& defaultValue )
		{
			return ( v.IsArray() && v.Size() == 4 && v[0].IsDouble() ) ? float4( static_cast<float>( v[0].GetDouble() ), static_cast<float>( v[1].GetDouble() ), static_cast<float>( v[2].GetDouble() ), static_cast<float>( v[3].GetDouble() ) ) : defaultValue;
		}

		float4x4 FileJson::read( const Value& v, const float4x4& defaultValue )
		{
			if( v.IsArray() && v.Size() == 16 && v[0].IsDouble() )
			{
				float4x4 ret;
				for( int i = 0; i < 16; ++i )
				{
					ret[i] = static_cast<float>( v[i].GetDouble() );
				}
				return ret;
			}
			return defaultValue;
		}

		double FileJson::read( const Value& v, const double& defaultValue )
		{
			return v.IsDouble() ? v.GetDouble() : defaultValue;
		}

		String FileJson::read( const Value& v, const String& defaultValue )
		{
			return v.IsString() ? String( v.GetString() ) : defaultValue;
		}

		Array<boolean> FileJson::read( const Value& v, const Array<boolean>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsBool() )
			{
				Array<boolean> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( v[i].GetBool() );
				}
				return ret;
			}
			return defaultValue;
		}

		Array<int32> FileJson::read( const Value& v, const Array<int32>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsInt() )
			{
				Array<int32> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( v[i].GetInt() );
				}
				return ret;
			}
			return defaultValue;
		}

		Array<int64> FileJson::read( const Value& v, const Array<int64>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsInt64() )
			{
				Array<int64> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( v[i].GetInt64() );
				}
				return ret;
			}
			return defaultValue;
		}

		Array<uint32> FileJson::read( const Value& v, const Array<uint32>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsUint() )
			{
				Array<uint32> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( v[i].GetUint() );
				}
				return ret;
			}
			return defaultValue;
		}

		Array<uint64> FileJson::read( const Value& v, const Array<uint64>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsUint64() )
			{
				Array<uint64> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( v[i].GetUint64() );
				}
				return ret;
			}
			return defaultValue;
		}

		Array<float> FileJson::read( const Value& v, const Array<float>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsDouble() )
			{
				Array<float> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( static_cast<float>( v[i].GetDouble() ) );
				}
				return ret;
			}
			return defaultValue;
		}

		Array<double> FileJson::read( const Value& v, const Array<double>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsDouble() )
			{
				Array<double> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( v[i].IsDouble() );
				}
				return ret;
			}
			return defaultValue;
		}

		Array<String> FileJson::read( const Value& v, const Array<String>& defaultValue )
		{
			if( v.IsArray() && v.Size() > 0 && v[0].IsString() )
			{
				Array<String> ret;
				JSON_FOREACH_IN_ARRAY( i, v )
				{
					ret.add( String( v[i].GetString() ) );
				}
				return ret;
			}
			return defaultValue;
		}

		void FileJson::write( Value& v, const boolean& value )
		{
			v.SetBool( value );
		}

		void FileJson::write( Value& v, const int32& value )
		{
			v.SetInt( value );
		}

		void FileJson::write( Value& v, const int64& value )
		{
			v.SetInt64( value );
		}

		void FileJson::write( Value& v, const uint32& value )
		{
			v.SetUint( value );
		}

		void FileJson::write( Value& v, const uint64& value )
		{
			v.SetUint64( value );
		}

		void FileJson::write( Value& v, const float& value )
		{
			v.SetDouble( static_cast<double>( value ) );
		}

		void FileJson::write( Value& v, const double& value )
		{
			v.SetDouble( value );
		}

		void FileJson::write( Value& v, const String& value )
		{
			v.SetString( rapidjson::StringRef( value.getCStr() ) );
		}

		void FileJson::write( Value& v, const Array<boolean>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( value[i], jdoc.GetAllocator() );
			}
		}

		void FileJson::write( Value& v, const Array<int32>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( value[i], jdoc.GetAllocator() );
			}
		}

		void FileJson::write( Value& v, const Array<int64>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( value[i], jdoc.GetAllocator() );
			}
		}

		void FileJson::write( Value& v, const Array<uint32>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( value[i], jdoc.GetAllocator() );
			}
		}

		void FileJson::write( Value& v, const Array<uint64>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( value[i], jdoc.GetAllocator() );
			}
		}

		void FileJson::write( Value& v, const Array<float>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( value[i], jdoc.GetAllocator() );
			}
		}

		void FileJson::write( Value& v, const Array<double>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( value[i], jdoc.GetAllocator() );
			}
		}

		void FileJson::write( Value& v, const Array<String>& value, Document& jdoc )
		{
			v.SetArray();
			for( int i = 0; i < value.getCount(); ++i )
			{
				v.PushBack( rapidjson::StringRef( value[i].getCStr() ), jdoc.GetAllocator() );
			}
		}
	}
}