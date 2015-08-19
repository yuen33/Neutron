#pragma once

#include "Array.h"
#include "String.h"
#include "NeutronFoundationCommon.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

using Neutron::Math::float2;
using Neutron::Math::float3;
using Neutron::Math::float4;
using Neutron::Math::float4x4;
using Neutron::Container::Array;
using Neutron::Container::String;
using namespace rapidjson;

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE FileJson
		{
		public:
			typedef rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>		Allocator;
			typedef rapidjson::Document											Document;
			typedef rapidjson::Value											Value;
			typedef rapidjson::Value::Member									Member;
			typedef rapidjson::Value::MemberIterator							MemberIterator;
			typedef rapidjson::Value::ConstMemberIterator						ConstMemberIterator;
			typedef rapidjson::Value::ValueIterator								ValueIterator;
			typedef rapidjson::Value::ConstValueIterator						ConstValueIterator;
			typedef rapidjson::SizeType											SizeType;

		public:
			FileJson();
			virtual ~FileJson();

			static boolean load( Document& jdoc, const char* path );
			static void save( const Document& jdoc, const char* path );
			static const char* getErrorMessage( const Document& jdoc );

			static boolean existBooleanMember( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsBool(); }
			static boolean existInt32Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsInt(); }
			static boolean existInt64Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsInt64(); }
			static boolean existUInt32Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsUint(); }
			static boolean existUInt64Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsUint64(); }			
			static boolean existFloatMember( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsDouble(); }
			static boolean existFloat2Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsArray() && jvalue[name].Size() == 2; }
			static boolean existFloat3Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsArray() && jvalue[name].Size() == 3; }
			static boolean existFloat4Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsArray() && jvalue[name].Size() == 4; }
			static boolean existFloat4x4Member( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsArray() && jvalue[name].Size() == 16; }
			static boolean existDoubleMember( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsDouble(); }
			static boolean existStringMember( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsString(); }
			static boolean existObjectMember( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsObject(); }
			static boolean existArrayMember( const Value& jvalue, const char* name ) { return jvalue.IsObject() && jvalue.HasMember( name ) && jvalue[name].IsArray(); }

			static boolean tryRead( const Value& v, boolean& ret );
			static boolean tryRead( const Value& v, int32& ret );
			static boolean tryRead( const Value& v, int64& ret );
			static boolean tryRead( const Value& v, uint32& ret );
			static boolean tryRead( const Value& v, uint64& ret );
			static boolean tryRead( const Value& v, float& ret );
			static boolean tryRead( const Value& v, float2& ret );
			static boolean tryRead( const Value& v, float3& ret );
			static boolean tryRead( const Value& v, float4& ret );
			static boolean tryRead( const Value& v, float4x4& ret );
			static boolean tryRead( const Value& v, double& ret );
			static boolean tryRead( const Value& v, String& ret );
			static boolean tryRead( const Value& v, Array<boolean>& ret );
			static boolean tryRead( const Value& v, Array<int32>& ret );
			static boolean tryRead( const Value& v, Array<int64>& ret );
			static boolean tryRead( const Value& v, Array<uint32>& ret );
			static boolean tryRead( const Value& v, Array<uint64>& ret );
			static boolean tryRead( const Value& v, Array<float>& ret );
			static boolean tryRead( const Value& v, Array<double>& ret );
			static boolean tryRead( const Value& v, Array<String>& ret );

			static boolean read( const Value& v, const boolean& defaultValue );
			static int32 read( const Value& v, const int32& defaultValue );
			static int64 read( const Value& v, const int64& defaultValue );
			static uint32 read( const Value& v, const uint32& defaultValue );
			static uint64 read( const Value& v, const uint64& defaultValue );
			static float read( const Value& v, const float& defaultValue );
			static float2 read( const Value& v, const float2& defaultValue );
			static float3 read( const Value& v, const float3& defaultValue );
			static float4 read( const Value& v, const float4& defaultValue );
			static float4x4 read( const Value& v, const float4x4& defaultValue );
			static double read( const Value& v, const double& defaultValue );
			static String read( const Value& v, const String& defaultValue );
			static Array<boolean> read( const Value& v, const Array<boolean>& defaultValue );
			static Array<int32> read( const Value& v, const Array<int32>& defaultValue );
			static Array<int64> read( const Value& v, const Array<int64>& defaultValue );
			static Array<uint32> read( const Value& v, const Array<uint32>& defaultValue );
			static Array<uint64> read( const Value& v, const Array<uint64>& defaultValue );
			static Array<float> read( const Value& v, const Array<float>& defaultValue );
			static Array<double> read( const Value& v, const Array<double>& defaultValue );
			static Array<String> read( const Value& v, const Array<String>& defaultValue );			

			static void write( Value& v, const boolean& value );
			static void write( Value& v, const int32& value );
			static void write( Value& v, const int64& value );
			static void write( Value& v, const uint32& value );
			static void write( Value& v, const uint64& value );
			static void write( Value& v, const float& value );
			static void write( Value& v, const double& value );
			static void write( Value& v, const String& value );
			static void write( Value& v, const Array<boolean>& value, Document& jdoc );
			static void write( Value& v, const Array<int32>& value, Document& jdoc );
			static void write( Value& v, const Array<int64>& value, Document& jdoc );
			static void write( Value& v, const Array<uint32>& value, Document& jdoc );
			static void write( Value& v, const Array<uint64>& value, Document& jdoc );
			static void write( Value& v, const Array<float>& value, Document& jdoc );
			static void write( Value& v, const Array<double>& value, Document& jdoc );
			static void write( Value& v, const Array<String>& value, Document& jdoc );
		};

#define JSON_FOREACH_IN_OBJECT( it, jobject ) for( Neutron::Utility::FileJson::MemberIterator( it ) = ( jobject ).MemberBegin(); ( it ) != ( jobject ).MemberEnd(); ++it )
#define JSON_FOREACH_CONST_IN_OBJECT( it, jobject ) for( Neutron::Utility::FileJson::ConstMemberIterator( it ) = ( jobject ).MemberBegin(); ( it ) != ( jobject ).MemberEnd(); ++it )
#define JSON_FOREACH_IN_ARRAY( i, jarray ) for( Neutron::Utility::FileJson::SizeType ( i ) = 0; i < ( jarray ).Size(); ++i )
	}
}