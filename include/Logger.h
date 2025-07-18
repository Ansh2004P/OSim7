// Logger.h
#pragma once
#include <string>

enum class LogLevel {
    INFO,
    WARN,
    ERROR,
    SUCCESS
};

class Logger {
public:
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);
    static void success(const std::string& message);

private:
    static void log(LogLevel level, const std::string& message);
    static std::string getTimestamp();
    static std::string getLevelTag(LogLevel level);
#ifndef _WIN32
    static std::string getColor(LogLevel level);
#endif
};
