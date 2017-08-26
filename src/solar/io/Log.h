#pragma once

#include <cstdio>
#include <string>
#include <ostream>

#include "..\core\Object.h"
#include "..\Common.h"

#include <sstream>

namespace solar
{

	/// Debug message level. By default only shown in debug mode.
	static const int LOG_DEBUG = 0;
	/// Informative message level.
	static const int LOG_INFO = 1;
	/// Warning message level.
	static const int LOG_WARNING = 2;
	/// Error message level.
	static const int LOG_ERROR = 3;
	/// Disable all log messages.
	static const int LOG_NONE = 4;

	class Packet
	{
	public:
		Packet(int level) :
			m_level(level)
		{
		}

		template <typename T>
		Packet& operator<<(const T& data)
		{
			m_message << data;
			return *this;
		}

		int getLevel() const { return m_level; }
		std::string getMessage() const { return m_message.str(); }

	private:
		const int m_level;
		std::stringstream m_message;
	};

	class SOLAR_API Log : public Object
	{
		SOLAR_OBJECT(Log)
	public:
		Log(Context* context);
		virtual ~Log();

		void setLevel(int level);
		void enableTimestamp(bool enable);

		int getLevel() const { return m_level; }
		bool isTimestampEnabled() const { return m_timestampEnabled; }
		std::string getLastMessage() const { return m_lastMessage; }

		void operator+=(const Packet& packet) 
		{
			write(packet.getLevel(), packet.getMessage());
		}

		static void write(int level, const std::string& message);
		static Log* getInstance();

	private:
		std::string m_lastMessage;
		int m_level;
		bool m_timestampEnabled;
		bool m_inWrite;
	};

	#ifdef SOLAR_LOGGING
	#define SOLAR_LOGDEBUG() (*solar::Log::getInstance()) += solar::Packet(solar::LOG_DEBUG)
	#define SOLAR_LOGINFO() (*solar::Log::getInstance()) += solar::Packet(solar::LOG_INFO)
	#define SOLAR_LOGWARNING() (*solar::Log::getInstance()) += solar::Packet(solar::LOG_WARNING)
	#define SOLAR_LOGERROR() (*solar::Log::getInstance()) += solar::Packet(solar::LOG_ERROR)
	#else
	#define SOLAR_LOGDEBUG(message) ((void)0)
	#define SOLAR_LOGINFO(message) ((void)0)
	#define SOLAR_LOGWARNING(message) ((void)0)
	#define SOLAR_LOGERROR(message) ((void)0)
	#endif // SOLAR_LOGGING

}