#include <Logger.h>
#include <iostream>
#include <ctime>

LogLevel Logger::_maxLevel = LogLevel::ERROR;

Logger& Logger::instance() {
	static Logger logger;
	return logger;
}

void Logger::log(LogLevel level, const std::string& message) const {
	if (level <= _maxLevel) {
		std::cerr << timestamp() << " " << toString(level) << ": " << message << std::endl;
	}
}

void Logger::setLoggingLevel(LogLevel maxLevel) {
	_maxLevel = maxLevel;
}

std::string Logger::timestamp() const {
	time_t t;
	tm* timeinfo;
	std::time(&t);
	timeinfo = localtime(&t);
	char buffer[80];
	strftime(buffer, 80, "%F-%H-%M-%S", timeinfo);
	std::string str(buffer);
	return str;
}

const std::string Logger::toString(LogLevel level) const {
	switch (level) {
		case OFF:     return "OFF    "; break;
		case ERROR:   return "ERROR  "; break;
		case WARNING: return "WARNING"; break;
		case INFO:    return "INFO   "; break;
		case DEBUG:   return "DEBUG  "; break;
		case TRACE:   return "TRACE  "; break;
		default:      return "<DEF>  "; break;
	}
}