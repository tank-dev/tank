#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

class Logger
{
public:
    Logger(std::string file);
    ~Logger();

    void log(std::string logStr);

private:
    std::string _logFile;
};

#endif
