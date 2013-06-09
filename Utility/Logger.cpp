#include "Logger.hpp"

// temp!!! 
// This is so it will output to the command line. It should be done in CMake
// but I'm to tired to work out how to do that right now.
#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

Logger::Logger(std::string file)
    : _logFile(file) {}

Logger::~Logger() 
{
}

void Logger::log(std::string logStr)
{
    std::ofstream log_file(_logFile + ".log", std::ios_base::out | std::ios_base::app);
    log_file << logStr << std::endl;
#ifdef DEBUG
    std::cout << "["
        << _logFile
        << "] "
        << logStr
        << std::endl;
#endif
}
