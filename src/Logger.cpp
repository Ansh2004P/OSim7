// Logger.cpp

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#ifdef ERROR
#undef ERROR
#endif
#endif

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&t_now);

    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::getLevelTag(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARN:    return "WARN";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::SUCCESS: return "SUCCESS";
        default:                return "LOG";
    }
}

#ifdef _WIN32
void setConsoleColor(LogLevel level) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = 7; // Default gray

    switch (level) {
        case LogLevel::INFO:
            color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break;
        case LogLevel::WARN:
            color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break;
        case LogLevel::ERROR:
            color = FOREGROUND_RED | FOREGROUND_INTENSITY;
            break;
        case LogLevel::SUCCESS:
            color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break;
        default:
            color = 7;
            break;
    }

    SetConsoleTextAttribute(hConsole, color);
}

void resetConsoleColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // Default gray
}
#else
std::string Logger::getColor(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:    return "\033[32m"; // Green
        case LogLevel::WARN:    return "\033[33m"; // Yellow
        case LogLevel::ERROR:   return "\033[31m"; // Red
        case LogLevel::SUCCESS: return "\033[36m"; // Cyan
        default:                return "\033[0m";  // Reset
    }
}
#endif

void Logger::log(LogLevel level, const std::string& message) {
    std::string time = getTimestamp();
    std::string tag = getLevelTag(level);
    std::ostream& out = (level == LogLevel::ERROR) ? std::cerr : std::cout;

    std::ostringstream formatted;
    formatted << std::left
              << std::setw(20) << time
              << std::setw(10) << tag
              << message;

#ifdef _WIN32
    setConsoleColor(level);
    out << formatted.str() << std::endl;
    resetConsoleColor();
#else
    std::string color = getColor(level);
    out << color << formatted.str() << "\033[0m" << std::endl;
#endif
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::WARN, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::success(const std::string& message) {
    log(LogLevel::SUCCESS, message);
}
