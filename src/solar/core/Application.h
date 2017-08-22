#pragma once

#include <iostream>
#include <memory>

#include "Object.h"
#include "Context.h"
#include "Engine.h"

namespace solar
{
	class Engine;

	class SOLAR_API ApplicationAdapter : public Object
	{
		SOLAR_OBJECT(ApplicationAdapter)
	public:
		ApplicationAdapter(Context* context) :
			Object(context)
		{
			subscribeToEvent("update", SOLAR_HANDLER(ApplicationAdapter, handleUpdate));
			subscribeToEvent("render", SOLAR_HANDLER(ApplicationAdapter, handleRender));
			subscribeToEvent("window_resized", SOLAR_HANDLER(ApplicationAdapter, handleResize));
		}

		virtual ~ApplicationAdapter() {	}
	
		virtual void setup() { 	}

		virtual void start() {	}

		virtual void stop() {  }

		virtual void handleUpdate(const char* eventType, EventParameters& params) {	 }

		virtual void handleRender(const char* eventType, EventParameters& params) {	 }

		virtual void handleResize(const char* eventType, EventParameters& params) {	 }

	};

	class SOLAR_API Application : public Object
	{
		SOLAR_OBJECT(Application)
	public:
		Application(Context* context, ApplicationAdapter* adapter);

		int run();
	protected:
		std::shared_ptr<Engine> engine;

		int m_exitCode;

		ApplicationAdapter* m_adapter;

	};

} //solar
