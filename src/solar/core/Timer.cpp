#include "Timer.h"

#include <ctime>
#include <chrono>
#include <algorithm>

namespace solar
{


	Time::Time(Context* context) :
		Object(context),
		m_frameNumber(0),
		m_timestep(0.0f)
	{
	
	}

	Time::~Time()
	{
	}

	static long long tick()
	{
	
	}

	void Time::beginFrame(float timestep)
	{
		++m_frameNumber;
		if (!m_frameNumber)
			++m_frameNumber;

		m_timestep = timestep;
	}

	void Time::endFrame()
	{

	}

	float Time::getElapsedTime() 
	{
		return 0.0f;
	}

	unsigned Time::getSystemTime()
	{
		return (unsigned)0;
	}

	std::string Time::getTimeStamp()
	{
		time_t sysTime;
		time(&sysTime);
		const char* dateTime = ctime(&sysTime);
		std::string str(dateTime);
		std::replace(str.begin(), str.end(), '\n', ' ');
		return str;
	}

	using clock = std::chrono::high_resolution_clock;
	using namespace std::chrono_literals;

	Timer::Timer() :
		lag(0ns)
	{
		reset();
	}

	void Timer::start()
	{
		auto deltaTime = clock::now() - m_startTime;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	}

	void Timer::reset()
	{
		m_startTime = clock::now();
	}

	void Timer::setTimestep(long long timestep)
	{
		std::chrono::nanoseconds _timestep(1000000000LL/timestep);
		m_timestep = std::chrono::duration_cast<std::chrono::nanoseconds>(_timestep);
	}
}