#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

enum LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR_LEVEL,
    CRITICAL
};

class Logger
{
    public:
        static void setLevel(LogLevel level);
        static LogLevel getLevel();
        static void debug(const std::string& message);
        static void info(const std::string& message);
        static void warning(const std::string& message);
        static void error(const std::string& message);
        static void critical(const std::string& message);
    private:
        static LogLevel currentLevel;
        static std::string getCurrentTimestamp();
        static void log(LogLevel level, const std::string& levelStr, const std::string& message);
};

#endif // LOGGER_H
