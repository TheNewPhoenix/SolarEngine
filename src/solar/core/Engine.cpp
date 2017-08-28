#include "Engine.h"
#include "Context.h"
#include "Object.h"
#include "Timer.h"
#include "Application.h"
#include "..\graphics\Graphics.h"
#include "..\io\Log.h"
#include "..\input\Input.h"

#include <gl\GL.h>

namespace solar
{
	
	Engine::Engine(Context* context) :
		Object(context),
		m_timestep(0),
		m_targetFps(60),
		m_initialized(false),
		m_exiting(false)
	{
		m_context->registerSubsystem(this);
		
		m_context->registerSubsystem(new Time(m_context));
		m_context->registerSubsystem(new Graphics(m_context));
		m_context->registerSubsystem(new Log(m_context));
		m_context->registerSubsystem(new Input(m_context));

		m_frameTimer.setTimestep(m_targetFps);

		subscribeToEvent("windowclosed", SOLAR_HANDLER(Engine, handleExit));
	}

	Engine::~Engine()
	{
	}

	bool Engine::initialize()
	{
		if (m_initialized)
			return true;

		m_initialized = true;
		return true;
	}

	void Engine::setTargetFps(int fps)
	{}

	void Engine::runFrame()
	{
		m_frameTimer.start();
		m_frameTimer.reset();

		while (m_frameTimer.lag >= m_frameTimer.getTimestep())
		{
			m_frameTimer.lag -= m_frameTimer.getTimestep();
			update();
		}

		render();

	}

	void Engine::update()
	{
		EventParameters params;
		params["timestep"] = (float)m_frameTimer.getTimestep().count();
		sendEvent("update", params);
	}

	void Engine::render()
	{
		Input* input = GetSubsystem<Input>();
		input->update();

		Graphics* graphics = GetSubsystem<Graphics>();
		graphics->beginFrame();

		EventParameters params;
		params["timestep"] = (float)m_frameTimer.getTimestep().count();
		sendEvent("render", params);

		graphics->endFrame();
	}

	void Engine::exit()
	{}
	
	void Engine::handleExit(const char* eventType, EventParameters& parameters)
	{
		SOLAR_LOGDEBUG() << "handle exit: " << eventType;
		doExit();
	}

	void Engine::doExit()
	{
		m_exiting = true;
	}

}