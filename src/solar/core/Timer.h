#pragma once

#include <string>
#include <chrono>

#include "Object.h"
#include "Context.h"

namespace solar
{
	class SOLAR_API Timer
	{
	public:
		Timer();

		void start();

		void reset();
	
		std::chrono::nanoseconds lag;

		void setTimestep(long long timestep);

		auto getTimestep() { return m_timestep; }

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;

		std::chrono::nanoseconds m_timestep;

	};

	class Time : public Object
	{
		SOLAR_OBJECT(Time)
	public:
		Time(Context* context);

		virtual ~Time();

		void beginFrame(float timestep);

		void endFrame();

		unsigned getFrameNumber() const { return m_frameNumber; }

		float getTimestep() const { return m_timestep; }

		float getElapsedTime();

		static unsigned getSystemTime();
		static std::string getTimeStamp();

	private:

		unsigned m_frameNumber;
		float m_timestep;
	};
}