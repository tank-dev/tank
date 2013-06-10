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

    void log(std::string logStr);

private:
    std::string _logFile;
    Timer _timer;
};

#endif
