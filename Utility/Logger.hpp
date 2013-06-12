#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Timer.hpp"
#include <string>
#include <iostream>
#include <fstream>

class Logger
{
    std::string fileName_;
    Timer timer_;
    std::ofstream logFile_;

    class LogHelper
    {
        Logger& enclosing_;
    public:
        explicit LogHelper(Logger& enclosing) : enclosing_(enclosing) {}
        template <typename T> LogHelper& operator<< (const T& t) {
            enclosing_.logFile_ << t;
#ifdef DEBUG
            std::clog << t;
#endif
            return *this;
        }
    } logHelper_{*this};

public:
    Logger(std::string file);
    ~Logger();

    template <typename T>
    LogHelper& operator<<(const T& t);
};

Logger::Logger(std::string file) : fileName_{file}, logFile_{fileName_}
{
    timer_.start();
    logFile_ << "["
        << file
        << ": "
        << timer_.getHumanTime()
        << "] "
        << "Log file created...";
#ifdef DEBUG
    std::clog << "["
        << file
        << ": "
        << timer_.getHumanTime()
        << "] "
        << "Log file created...";
#endif
}

Logger::~Logger()
{
    logHelper_ << '\n';
}

template <typename T>
Logger::LogHelper& Logger::operator<<(const T& t)
{
    logHelper_ << '\n' << "["
        << fileName_
        << ": "
        << timer_.getHumanTime()
        << "] "
        << t;

    return logHelper_;
}


#endif
