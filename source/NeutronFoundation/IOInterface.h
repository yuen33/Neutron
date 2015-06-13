#pragma once

#include "NeutronFoundationCommon.h"
#include "Stream.h"

namespace Neutron
{
	namespace Utility
	{
		class NEUTRON_FOUNDATION_CORE IOInterface : public Stream
		{
		public:
			IOInterface() {}
			virtual ~IOInterface() {};

			virtual void seekSet( int offset ) = 0;
			virtual void seekEnd( int offset ) = 0;
			virtual void seekCur( int offset ) = 0;
			virtual Size tell() const = 0;
			virtual boolean eof() const = 0;
			virtual void flush() = 0;
			virtual Size getSize() const = 0;
			virtual const char* getPath() const = 0;
			virtual boolean isValid() const = 0;
		};

		class NEUTRON_FOUNDATION_CORE IOStdFile : public IOInterface
		{
			FILE*		file;
			String		path;

			IOStdFile();

		public:
			IOStdFile( const char* path, const char* mode );
			virtual ~IOStdFile();
			virtual void seekSet( int offset );
			virtual void seekEnd( int offset );
			virtual void seekCur( int offset );
			virtual Size tell() const;
			virtual boolean eof() const;
			virtual void flush();
			virtual Size read( uint8* buffer, Size size );
			virtual Size write( uint8* buffer, Size size );
			virtual Size getSize() const;
			virtual inline const char* getPath() const { return path.getCStr(); }
			virtual inline boolean isValid() const { return file && !path.empty(); }
			inline FILE* getFileHandle() const { return file; }
		};

		class NEUTRON_FOUNDATION_CORE IOMemory : public IOInterface
		{
		protected:
			String		path;
			Size		size;
			uint8*		data;
			uint8*		ptr;

			IOMemory();

		public:
			IOMemory( const char* path, uint8* data, Size size );
			virtual ~IOMemory();
			virtual void seekSet( int offset );
			virtual void seekEnd( int offset );
			virtual void seekCur( int offset );
			virtual Size tell() const;
			virtual boolean eof() const;
			virtual inline void flush() {}
			virtual Size read( uint8* buffer, Size size );
			virtual Size write( uint8* buffer, Size size );
			virtual inline Size getSize() const { return size; }
			virtual inline const char* getPath() const { return path.getCStr(); }
			virtual inline boolean isValid() const { return ptr <= data && ptr >= data + size; }
		};

#ifdef VRLAB_WINDOWS_DESKTOP
		class VRLAB_CORE IOMap : public IOMemory
		{
			HANDLE		file;
			HANDLE		map;

			IOMap();
			boolean createFileMapping();
			void destroyFileMapping();

		public:
			IOMap( const char* path );
			virtual ~IOMap();
		};
#endif
	}
}