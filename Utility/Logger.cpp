#include "Logger.hpp"

Logger::Logger(std::string file) : fileName_{file}, logFile_{fileName_}
{
    timer_.start();
    logFile_ << "["
        << file
        << ": "
        << timer_.getHumanTime()
        << "] "
        << "Log file created..."
        << std::endl;
#ifdef DEBUG
    std::clog << "["
        << file
        << ": "
        << timer_.getHumanTime()
        << "] "
        << "Log file created..."
        << std::endl;
#endif
}

Logger::~Logger()
{
    logHelper_ << '\n';
}
