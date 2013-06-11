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
        logFile.close();
        return true;
    }
    // Something has gone wrong making this log file.
    return false;
}

Logger::~Logger() 
{
}

/*
template<typename... Args>
void Logger::log(const std::string& logStr, Args&&... args)
{
    std::ofstream logFile(_logFile + ".log", std::ios_base::out | std::ios_base::app);
    logFile << "["
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

    _log(logFile, logStr, std::forward<Args>(args)...);
}
*/

/*
void Logger::_log(std::ofstream& logFile)
{
    logFile
		<< std::endl;
#ifdef DEBUG
    std::cout
		<< std::endl;
#endif
    logFile.close();
}
*/

/*
template<typename... Args>
void Logger::_log(std::ofstream& logFile, const std::string& logStr, Args&&... args)
{
    logFile << logStr;
#ifdef DEBUG
    std::cout << logStr;
#endif
    
    _log(logFile, std::forward<Args>(args)...);
}
*/
