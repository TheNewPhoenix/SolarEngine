
#include "Application.h"
#include "Context.h"

#include <functional>
#include <iostream>
#include <string>
#include <pybind11\pybind11.h>

namespace solar
{

	Application::Application(Context* context, ApplicationAdapter* adapter) :
		Object(context),
		m_exitCode(EXIT_SUCCESS)
	{
		m_adapter = adapter;
		engine = std::make_shared<Engine>(context);
	}

	int Application::run() {

		m_adapter->setup();

		if (!engine->initialize())
		{
			return m_exitCode;
		}

		m_adapter->start();

		while (!engine->isExiting())
			engine->runFrame();

		m_adapter->stop();
		return m_exitCode;
	}
}