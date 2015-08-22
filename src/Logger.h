#ifndef LOGGER_H_INCL
#define LOGGER_H_INCL

#include <string>

enum LogLevel {
	OFF = 0,
	ERROR = 1,
	WARNING = 2,
	INFO = 3,
	DEBUG = 4,
	TRACE = 5
};

class Logger {

public:

	static Logger& instance();
	virtual void log(LogLevel, const std::string&) const;
	static void setLoggingLevel(LogLevel);
	std::string timestamp() const;

protected:

	static LogLevel _maxLevel;

	const std::string toString(LogLevel) const;

private:

	Logger() {}
	Logger(const Logger&) {}
	void operator=(const Logger&) {}

};

#define LOG(level, message) Logger::instance().log((level), (message))

#endif