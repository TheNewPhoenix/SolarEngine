	#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "Object.h"

namespace solar
{

	class SOLAR_API EventGroup
	{
	public:
		EventGroup()
		{
		}

		void add(Object* object);

		void remove(Object* object);

		std::vector<Object*> m_receivers;
	};

	class SOLAR_API Context
	{
		friend class Object;

	public:
		Context();

		~Context();

		void addEventReceiver(Object* object, const char* eventType);
		void removeEventReceiver(Object* object, const char* eventType);

		EventGroup* getEventGroup(const char* eventType)
		{
			return m_eventGroups[eventType].get();
		}

		void registerSubsystem(Object* subsystem);

		Object* getSubsystem(std::string typeName);

		template <class T> T* GetSubsystem() const;

	private:
		std::map<std::string, std::shared_ptr<EventGroup>> m_eventGroups;
		std::map<std::string, Object*> m_subsystems;
	};

	template <class T> T* Context::GetSubsystem() const { return static_cast<T*>(GetSubsystem(T::getTypeNameStatic())); }
}