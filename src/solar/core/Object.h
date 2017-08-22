#pragma once

#include <functional>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <boost\variant.hpp>
#include <boost\any.hpp>

#include "..\Types.h"

namespace solar
{

	class Context;
	class EventHandler;

	#define SOLAR_OBJECT(typeName) \
	public: \
		virtual const std::string getTypeName() const { return std::string(#typeName); } \
		static const std::string getTypeNameStatic() { return std::string(#typeName); }

	typedef boost::variant<int, double, long, long long, float, unsigned> EventParameter;
	typedef std::map<std::string, EventParameter> EventParameters;

	static EventParameters noParameters;

	class SOLAR_API Object
	{
	public:
		Object(Context *context);

		virtual ~Object();

		virtual const std::string getTypeName() const = 0;

		void onEvent(const char* eventType, EventParameters parameters);

		void subscribeToEvent(const char* eventType, EventHandler* handler);

		void unsubscribeToEvent(const char* eventType);

		void unsubscribeToAllEvents();

		void sendEvent(const char* eventType, EventParameters parameters = noParameters);

		EventHandler* getEventHandler(const char* eventType);

		Object* getSubsystem(std::string typeName) const;

		template <class T> T* GetSubsystem() const;
	
	protected:
		Context* m_context;

	private:
		std::map<std::string, std::shared_ptr<EventHandler>> m_eventHandlers;
	};

	template <class T> T* Object::GetSubsystem() const { return static_cast<T*>(getSubsystem(T::getTypeNameStatic())); }

	class SOLAR_API EventHandler
	{
	public:
		EventHandler(Object* receiver) :
			m_receiver(receiver)
		{
		}

		virtual ~EventHandler() { }

		void setEventType(const char* eventType)
		{
			m_eventType = eventType;
		}

		virtual void invoke(EventParameters& parameters) = 0;

		Object* getReceiver() { return m_receiver; }
		
		std::string getEventType() { return m_eventType; }


	protected:
		Object* m_receiver;

		const char* m_eventType;
			
	};

	template <class T> class SOLAR_API EventHandlerImpl : public EventHandler
	{
	public:
		typedef void (T::*HandlerFunctionPtr)(const char*, EventParameters&);

		EventHandlerImpl(T* reciever, HandlerFunctionPtr function) :
			EventHandler(reciever),
			m_function(function)
		{
			assert(reciever);
			assert(m_function);
		}

		virtual void invoke(EventParameters& parameters)
		{
			T* receiver = static_cast<T*>(m_receiver);
			(receiver->*m_function)(m_eventType, parameters);
		}


	private:
		HandlerFunctionPtr m_function;
	};

	struct EventNameRegistry
	{
		static const char* registerEventName(const char* eventName);

		static const std::string& getEventName(const char* eventName);

		static std::map<const char*, std::string>& getEventNameMap();
	};

	#define SOLAR_EVENT(eventID, eventName) static const char* eventID = solar::EventNameRegistry::registerEventName(#eventName); namespace eventName

	#define SOLAR_HANDLER(classname, function) (new solar::EventHandlerImpl<classname>(this, &classname::function))
}