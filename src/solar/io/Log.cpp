#include "Log.h"
#include "..\core\Timer.h"

namespace solar
{
	
	const char* logLevelPrefixes[] =
	{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		0
	};

	static Log* logInstance = 0;

	Log::Log(Context* context) :
		Object(context),
		m_level(LOG_DEBUG),
		m_timestampEnabled(true),
		m_inWrite(false)
	{
		logInstance = this;
	}

	Log::~Log()
	{
		logInstance = 0;
		m_out = 0;
	}

	void Log::setLevel(int level)
	{
		if (level < LOG_DEBUG || level > LOG_NONE)
		{
			SOLAR_LOGERROR("Cannot use this log level.");
			return;
		}

		m_level = level;
	}

	void Log::enableTimestamp(bool enable)
	{
		m_timestampEnabled = enable;
	}

	void Log::setStream(std::ostream* stream)
	{
		m_out = stream;
	}

	Log* Log::log(int level)
	{
		return logInstance;
	}

	void Log::write(int level, const std::string& message)
	{
		if (level < LOG_DEBUG || level > LOG_NONE)
			return;
		
		if (!logInstance || logInstance->m_level > level || logInstance->m_inWrite)
			return;


		std::string formattedMessage = logLevelPrefixes[level];
		formattedMessage += ": " + message;
		logInstance->m_lastMessage = message;

		if (logInstance->m_timestampEnabled)
			formattedMessage = "[" + Time::getTimeStamp() + "]" + formattedMessage;

		formattedMessage += "\n";

		printf("%s", formattedMessage.c_str());
	}

}