#pragma once

#include "Object.h"
#include "Timer.h"

namespace solar
{
	class SOLAR_API Engine : public Object
	{
		SOLAR_OBJECT(Engine)
	public:
		Engine(Context* context);

		virtual ~Engine();

		bool initialize();

		void setTargetFps(int fps);

		void runFrame();

		bool isExiting() const { return m_exiting; };

		void update();

		void render();

		void exit();
	private:
		void handleExit(const char* eventType, EventParameters& parameters);

		void doExit();

		float m_timestep;

		unsigned m_targetFps;

		bool m_initialized;

		bool m_exiting;

		Timer m_frameTimer;

	};
}