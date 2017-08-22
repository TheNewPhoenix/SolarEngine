
#include <algorithm>
#include <memory>
#include <iostream>

#include "Context.h"

namespace solar
{
	void EventGroup::add(Object* object)
	{
		if (object)
		{
			m_receivers.push_back(object);
		}

	}

	void EventGroup::remove(Object* object)
	{
		std::vector<Object*>::iterator it;
		it = std::find(m_receivers.begin(), m_receivers.end(), object);
		m_receivers.erase(it);
	}

	Context::Context()
	{
	}

	Context::~Context()
	{
		m_subsystems.clear();
	}

	void Context::addEventReceiver(Object* object, const char* eventType)
	{
		
		std::shared_ptr<EventGroup>& group = m_eventGroups[eventType];
		if (!group)
			group = std::make_shared<EventGroup>();
		
		group->add(object);
	}

	void Context::removeEventReceiver(Object* object, const char* eventType)
	{
		EventGroup* group = getEventGroup(eventType);
		if (group)
			group->remove(object);
	}

	void Context::registerSubsystem(Object* object)
	{
		if (!object)
			return;

		m_subsystems[object->getTypeName()] = (object);
	}

	Object* Context::getSubsystem(std::string typeName)
	{
		return m_subsystems[typeName];
	}

}