#include "FileJson.h"
#include "IOInterface.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"

using Neutron::Utility::IOStdFile;

namespace Neutron
{
	namespace File
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

		boolean FileJson::read( const Value& v, boolean& ret )
		{
			if( v.IsBool() )
			{
				ret = v.GetBool();
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, int32& ret )
		{
			if( v.IsInt() )
			{
				ret = v.GetInt();
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, int64& ret )
		{
			if( v.IsInt64() )
			{
				ret = v.GetInt64();
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, uint32& ret )
		{
			if( v.IsUint() )
			{
				ret = v.GetUint();
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, uint64& ret )
		{
			if( v.IsUint64() )
			{
				ret = v.GetUint64();
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, float& ret )
		{
			if( v.GetDouble() )
			{
				ret = static_cast<float>( v.GetDouble() );
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, double& ret )
		{
			if( v.IsDouble() )
			{
				ret = v.GetDouble();
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, String& ret )
		{
			if( v.IsString() )
			{
				ret = v.GetString();
				return true;
			}
			return false;
		}

		boolean FileJson::read( const Value& v, Array<boolean>& ret )
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

		boolean FileJson::read( const Value& v, Array<int32>& ret )
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

		boolean FileJson::read( const Value& v, Array<int64>& ret )
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

		boolean FileJson::read( const Value& v, Array<uint32>& ret )
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

		boolean FileJson::read( const Value& v, Array<uint64>& ret )
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

		boolean FileJson::read( const Value& v, Array<float>& ret )
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

		boolean FileJson::read( const Value& v, Array<double>& ret )
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

		boolean FileJson::read( const Value& v, Array<String>& ret )
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