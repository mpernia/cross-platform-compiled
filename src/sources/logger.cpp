#include "../includes/logger.h"

using namespace std;

LogLevel Logger::currentLevel = INFO;

void Logger::setLevel(LogLevel level)
{
    currentLevel = level;
}

LogLevel Logger::getLevel()
{
    return currentLevel;
}

string Logger::getCurrentTimestamp()
{
    auto now = chrono::system_clock::now();
    auto time_t_now = chrono::system_clock::to_time_t(now);
    auto ms = chrono::duration_cast<chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    stringstream output;
    output << put_time(localtime(&time_t_now), "%Y-%m-%d %H:%M:%S");
    output << '.' << setfill('0') << setw(3) << ms.count();
    
    return output.str();
}

void Logger::log(LogLevel level, const string& levelStr, const string& message)
{
    if (level >= currentLevel) {
        cout << "[" << getCurrentTimestamp() << "] [" << levelStr << "] " << message << endl;
    }
}

void Logger::debug(const string& message)
{
    log(DEBUG, "DEBUG", message);
}

void Logger::info(const string& message)
{
    log(INFO, "INFO", message);
}

void Logger::warning(const string& message)
{
    log(WARNING, "WARNING", message);
}

void Logger::error(const string& message)
{
    log(ERROR_LEVEL, "ERROR", message);
}

void Logger::critical(const string& message)
{
    log(CRITICAL, "CRITICAL", message);
}
