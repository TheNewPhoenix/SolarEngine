#pragma once

#include <cstdio>
#include <string>
#include <ostream>

#include "..\core\Object.h"
#include "..\Common.h"

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
		void setStream(std::ostream* stream);

		template <typename T>
		Log& operator << (const T& object)
		{
			(*m_out) << object;
			return *this;
		}

		 
		static Log* log(int level);
		static void write(int level, const std::string& message);

	private:
		std::string m_lastMessage;
		int m_level;
		bool m_timestampEnabled;
		bool m_inWrite;

		std::ostream *m_out;
	};

	#ifdef SOLAR_LOGGING
	#define SOLAR_LOGDEBUG(message) solar::Log::write(solar::LOG_DEBUG, message)
	#define SOLAR_LOGINFO(message) solar::Log::write(solar::LOG_INFO, message)
	#define SOLAR_LOGWARNING(message) solar::Log::write(solar::LOG_WARNING, message)
	#define SOLAR_LOGERROR(message) solar::Log::write(solar::LOG_ERROR, message)
	#define SOLAR_DEBUG_LOG() solar::Log::log(solar::LOG_DEBUG)
	#else
	#define SOLAR_LOGDEBUG(message) ((void)0)
	#define SOLAR_LOGINFO(message) ((void)0)
	#define SOLAR_LOGWARNING(message) ((void)0)
	#define SOLAR_LOGERROR(message) ((void)0)
	#endif // SOLAR_LOGGING

}