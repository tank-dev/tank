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

void Logger::log(std::string logStr)
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
    log_file.close();
}
