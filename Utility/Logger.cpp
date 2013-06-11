#include "Logger.hpp"


Logger::Logger(std::string file)
    : _logFile(file),
      _timer()
{
}

bool Logger::initialize()
{
    std::ofstream logFile(_logFile + ".log", std::ios_base::out | std::ios_base::trunc);
    if (!logFile.fail())
    {
        _timer.start();
        logFile << "["
            << _logFile
            << ": "
            << _timer.getHumanTime()
            << "] "
            << "Log file created..."
            << std::endl;
#ifdef DEBUG
        std::cout << "["
            << _logFile
            << ": "
            << _timer.getHumanTime()
            << "] "
            << "Log file created..."
            << std::endl;
#endif
        logFile.close();
        return true;
    }
    // Something has gone wrong making this log file.
    return false;
}

Logger::~Logger() 
{
}
