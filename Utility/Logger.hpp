#pragma once
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

        typedef decltype(std::clog)& (*Manip)(decltype(std::clog)&);
        LogHelper& operator<< (Manip manip) {
            manip(std::clog);
            manip(enclosing_.logFile_);
            return *this;
        }
    } logHelper_{*this};

public:
    Logger(std::string file);
    ~Logger();

    template <typename T>
    LogHelper& operator<<(const T& t);
};

template <typename T>
Logger::LogHelper& Logger::operator<<(const T& t)
{
    logHelper_ << std::endl << "["
        << fileName_
        << ": "
        << timer_.getHumanTime()
        << "] "
        << t;

    return logHelper_;
}


#endif //LOGGER_HPP
