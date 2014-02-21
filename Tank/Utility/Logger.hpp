// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef TANK_LOGGER_HPP
#define TANK_LOGGER_HPP

#include "Timer.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

namespace tank
{

class Logger;

class Logger_buf : public std::stringbuf
{
    std::function<void(const std::string&)> log_fn;
public:

    Logger_buf(std::function<void(const std::string&)> log_fn) : log_fn(log_fn) {}
    int sync() override {
        log_fn(str());
        str("");
        return 0;
    }
};

class Logger : public std::ostream
{
    std::string fileName_;
    Timer timer_;
    std::ofstream logFile_;
    Logger_buf buf_;
public:
    Logger(std::string file);
    void log(const std::string& s);
	~Logger() throw() {}
};

}

#endif //LOGGER_HPP
