#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "Timer.hpp"

#include <fstream>

class Logger
{
public:
    Logger(std::string file);
    ~Logger();

    bool initialize();

    void log(const std::string& logStr);

    template<typename... Tail>
    void log(const std::string& logStr, Tail&&... tail);

private:
    std::string _logFile;
    Timer _timer;

    void _log(std::ofstream log_file, const std::string& logStr);

    template<typename... Tail>
    void _log(std::ofstream log_file, const std::string& logStr, Tail&&... tail);
};

#endif
