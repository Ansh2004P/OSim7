// Logger.cpp

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#ifdef ERROR
#undef ERROR
#endif
#endif

// Get current timestamp
std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&t_now);

    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Get string tag for log level
std::string Logger::getLevelTag(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:  return "INFO ";
        case LogLevel::WARN:  return "WARN ";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::SUCCESS: return "SUCCESS";
        default:              return "LOG  ";
    }
}

#ifdef _WIN32
// Set Windows console text color based on log level
void setConsoleColor(LogLevel level) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = 7; // Default gray

    switch (level) {
        case LogLevel::INFO:
            color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break;
        case LogLevel::WARN:
            color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break; // Yellow
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

// Reset color to default
void resetConsoleColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // Default gray
}
#else
// ANSI escape codes for color in non-Windows terminals
std::string Logger::getColor(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:  return "\033[32m"; // Green
        case LogLevel::WARN:  return "\033[33m"; // Yellow
        case LogLevel::ERROR: return "\033[31m"; // Red
        default:              return "\033[0m";
    }
}
#endif

// Generic log function
void Logger::log(LogLevel level, const std::string& message) {
    std::string time = getTimestamp();
    std::string tag = getLevelTag(level);
    std::ostream& out = (level == LogLevel::ERROR) ? std::cerr : std::cout;

#ifdef _WIN32
    setConsoleColor(level);
    out << "[" << time << "] "
        << "[" << tag << "] "
        << message << std::endl;
    resetConsoleColor();
#else
    std::string color = getColor(level);
    out << color
        << "[" << time << "] "
        << "[" << tag << "] "
        << message
        << "\033[0m" << std::endl;
#endif
}

// Specific level helpers
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
