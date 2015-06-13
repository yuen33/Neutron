#pragma once

#include "NeutronFoundationCommon.h"
#include "Array.h"
#include "Timer.h"
#include "Type.h"
#include "HandleManager.h"
#include "TaskManager.h"

using Neutron::Container::Array;
using Neutron::Concurrent::TaskPtr;
using Neutron::Concurrent::Task;
using Neutron::Concurrent::TaskManager;

namespace Neutron
{
	namespace Utility
	{
		template<typename MessageType>
		using Subscriber = std::function< void( const MessageType& ) >;

		template<typename MessageType>
		using SubscriberHandle = HandleConcrete<Subscriber<MessageType> >;

		template<typename MessageType>
		using SubscriberHandleManager = HandleManager<Subscriber<MessageType> >;

		template<typename MessageType>
		class MessageHandleTask : public Task
		{
			Subscriber<MessageType> subscriber;
			MessageType message;

			MessageHandleTask( Subscriber<MessageType> subscriber, MessageType message ) : subscriber( subscriber ), message( message ) {};
			virtual ~MessageHandleTask() {};

			virtual inline void deleteMethod( RCObject* object )
			{
				delete static_cast<MessageHandleTask*>( object );
			}

		public:
			typedef RCPtr<MessageHandleTask> MessageHandleTaskPtr;

			static TaskPtr create( Subscriber<MessageType> subscriber, MessageType message )
			{
				return TaskPtr( new MessageHandleTask( subscriber, message ) );
			}

			virtual inline void onStart()
			{
				if( subscriber )
				{
					subscriber( message );
				}
			}
		};

		template<int BusID = 0>
		class MessageBus
		{
			MessageBus( const MessageBus& other );
			MessageBus& operator=( const MessageBus& rhs );

		public:
			MessageBus() {};
			virtual ~MessageBus() {}

			template<typename MessageType>
			SubscriberHandle<MessageType> subscribe( Subscriber<MessageType> subscriber )
			{
				return subscriber ? SubscriberHandleManager<MessageType>::acquire( subscriber ) : 0;
			}
			
			template<typename MessageType>
			void unsubscribe( const SubscriberHandle<MessageType>& handle )
			{
				SubscriberHandleManager<MessageType>::release( handle );
			}
			
			template<typename MessageType>
			void publishBlocking( const MessageType& message )
			{
				for( uint32 i = 0; i < SubscriberHandleManager<MessageType>::getData().size(); ++i )
				{
					Subscriber<MessageType> subscriber = SubscriberHandleManager<MessageType>::getData()[i];
					if( subscriber )
					{
						subscriber( message );
					}
				}
			}

			template<typename MessageType>
			void publishAsync( const MessageType& message, TaskManager& taskManager )
			{
				for( uint32 i = 0; i < SubscriberHandleManager<MessageType>::getData().size(); ++i )
				{
					Subscriber<MessageType> subscriber = SubscriberHandleManager<MessageType>::getData()[i];
					while( !taskManager.assign( MessageHandleTask<MessageType>::create( subscriber, message ) ) );
				}
			}
		};
	}
}