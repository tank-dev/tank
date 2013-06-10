#include "Logger.hpp"

// temp!!! 
// This is so it will output to the command line. It should be done in CMake
// but I'm to tired to work out how to do that right now.
#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

Logger::Logger(std::string file)
    : _logFile(file),
      _timer()
{
}

bool Logger::initialize()
{
    std::ofstream log_file(_logFile + ".log", std::ios_base::out | std::ios_base::trunc);
    if (!log_file.fail())
    {
        _timer.start();
        log_file << "["
            << _logFile
            << ": "
            << _timer.getTicks()
            << "] "
            << "Log file created..."
            << std::endl;
#ifdef DEBUG
        std::cout << "["
            << _logFile
            << ": "
            << _timer.getTicks()
            << "] "
            << "Log file created..."
            << std::endl;
#endif
        log_file.close();
        return true;
    }
    // Something has gone wrong making this log file.
    return false;
}

Logger::~Logger() 
{
}

void Logger::log(const std::string& logStr)
{
    std::ofstream log_file(_logFile + ".log", std::ios_base::out | std::ios_base::app);
    log_file << "["
        << _logFile
        << ": "
        << _timer.getTicks()
        << "] "
        << logStr
        << std::endl;
#ifdef DEBUG
    std::cout << "["
        << _logFile
        << ": "
        << _timer.getTicks()
        << "] "
        << logStr
        << std::endl;
#endif
}

template<typename... Tail>
void Logger::log(const std::string& logStr, Tail&&... tail)
{
    std::ofstream log_file(_logFile + ".log", std::ios_base::out | std::ios_base::app);
    log_file << "["
        << _logFile
        << ": "
        << _timer.getTicks()
        << "] ";
#ifdef DEBUG
    std::cout << "["
        << _logFile
        << ": "
        << _timer.getTicks()
        << "] ";
#endif

    _log(log_file, logStr, std::forward<Tail>(tail)...);

	log_file << std::endl;
#ifdef DEBUG
    std::cout << std::endl;
#endif
    log_file.close();
}

void Logger::_log(std::ofstream log_file, const std::string& logStr)
{
    log_file << logStr;
#ifdef DEBUG
    std::cout << logStr;
#endif
}

template<typename... Tail>
void Logger::_log(std::ofstream log_file, const std::string& logStr, Tail&&... tail)
{
    log_file << logStr;
#ifdef DEBUG
    std::cout << logStr;
#endif
    
    _log(log_file, std::forward<Tail>(tail)...);
}
