#pragma once

#include "NeutronSystemCommon.h"
#include "DataStream.h"
#include "ProcessingUnit.h"

namespace Neutron
{
	namespace Engine
	{
		class NEUTRON_CORE Pin : public RCObject
		{
		public:
			// pin direction
			enum : int
			{
				PD_Unknown,
				PD_Input,
				PD_Output,
			};

		private:
			int direction;
			String name;

		public:
			Pin();
			Pin( int direction );
			virtual ~Pin();

			virtual void attach( ProcessingUnitPtr unit );
			virtual void attach( ResourcePtr unit );
			virtual void dettach();

			virtual void getData( ProcessingUnitPtr& outData );
			virtual void getData( ResourcePtr& outData );

			virtual boolean isIdle() = 0;
			inline int getDirection() const { return direction; }
			inline void setName( const char* name ) { this->name = name; }
			inline const char* getName() const { return name.getCStr(); }
		};

		template<typename T>
		class PinConcrete : public Pin
		{
			RCPtr<T> data;

		public:
			static PinPtr createPin( int direction )
			{
				return PinPtr( new PinConcrete<T>( direction ) );
			}
			PinConcrete( int direction ) : Pin( direction ) {}
			virtual ~PinConcrete() {};

			inline void attach( RCPtr<T> attachment ) { data = attachment; }
			inline void dettach() { data = RCPtr<T>::null; }

			inline virtual void getData( RCPtr<T>& outData ) { outData = data; }
			inline virtual boolean isIdle() { return data.isNull(); }
		};

		typedef PinConcrete<ProcessingUnit> ProcessingUnitPin;
		typedef PinConcrete<Resource>		ResourcePin;

		typedef RCPtr<ProcessingUnitPin>	ProcessingUnitPinPtr;
		typedef RCPtr<ResourcePin>			ResourcePinPtr;

		/*class NEUTRON_CORE ProcessingUnitPin : public Pin
		{
			int acceptProcessingUnitType;

		public:
			ProcessingUnitPin( int acceptProcessingUnitType ) : acceptProcessingUnitType( acceptProcessingUnitType ) { pinType = PT_ProcessingUnit; }
			virtual ~ProcessingUnitPin() {}
		};

		class NEUTRON_CORE ResourceStreamPin : public Pin
		{
			int acceptResourceType;

		public:
			ResourceStreamPin( int acceptResourceType ) : acceptResourceType( acceptResourceType ) { pinType = PT_ResourceStream; }
			virtual ~ResourceStreamPin() {}
		};*/
	}
}