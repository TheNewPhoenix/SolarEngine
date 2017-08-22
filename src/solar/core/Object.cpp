
#include <iostream>

#include "Object.h"
#include "Context.h"

namespace solar
{

	Object::Object(Context* context) :
		m_context(context)
	{
		assert(m_context);
	}

	Object::~Object()
	{
		unsubscribeToAllEvents();
	}

	void Object::onEvent(const char* eventType, EventParameters parameters)
	{
		EventHandler* handler = getEventHandler(eventType);
		if (handler)
			handler->invoke(parameters);
	}

	void Object::subscribeToEvent(const char* eventType, EventHandler* handler)
	{

		if (!handler)
			return;
		
		handler->setEventType(eventType);

		m_eventHandlers[eventType] = std::shared_ptr<EventHandler>(handler);
		m_context->addEventReceiver(this, eventType);

	}

	void Object::unsubscribeToEvent(const char* eventType)
	{
		
	}

	void Object::unsubscribeToAllEvents()
	{
		
	}

	void Object::sendEvent(const char* eventType, EventParameters parameters)
	{
		EventGroup* group = m_context->getEventGroup(eventType);
		if (group)
		{

			for (unsigned i = 0; i < group->m_receivers.size(); i++)
			{
				Object* receiver = group->m_receivers[i];
				if (!receiver)
					continue;

				receiver->onEvent(eventType, parameters);
			}
		}
	}

	Object* Object::getSubsystem(std::string typeName) const
	{
		return m_context->getSubsystem(typeName);
	}

	EventHandler* Object::getEventHandler(const char* eventType)
	{
		return m_eventHandlers[eventType].get();
	}

}