#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "Timer.hpp"

#include <fstream>

// temp!!! 
// This is so it will output to the command line. It should be done in CMake
// but I'm to tired to work out how to do that right now.
#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

class Logger
{
public:
    Logger(std::string file);
    ~Logger();

	/**
	 * @brief Initializes the log file. This involves deleting any existing log
	 * file of the same name and creating a new one. This also starts the log
	 * timer. Be careful not to make 2 logs of the same name.
	 *
	 * @return True if the logfile was created successfully
	 */
    bool initialize();

	/**
	 * @brief Logs a message in a variable number of parts.
	 *
	 * @param logStr The first bit of the message.
	 * @param args The rest of the message.
	 */
    template<typename... Args>
    void log(const std::string& logStr, Args&&... args);

private:
    std::string _logFile;
    Timer _timer;

    template<typename... Args>
    void _log(std::ofstream& logFile, const std::string& logStr, Args&&... args);
    void _log(std::ofstream& logFile);
};

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

template<typename... Args>
void Logger::_log(std::ofstream& logFile, const std::string& logStr, Args&&... args)
{
	logFile << logStr;
#ifdef DEBUG
	std::cout << logStr;
#endif
	_log(logFile, std::forward<Args>(args)...);
}

inline
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

#endif
