// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

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
    std::function<void(const std::string&) > log_fn;

public:
    Logger_buf(std::function<void(const std::string&) > log_fn) : log_fn(log_fn)
    {
    }
    int sync() override
    {
        log_fn(str());
        str("");
        return 0;
    }
};

/*!
 * \brief A stream for logging debug information to a file.
 *
 * This acts like a standard ostream (_e.g._ `std::cout`).
 * If `DEBUG` is defined, it also outputs to `std::clog`.
 *
 * Tank writes to Game::log when initializing and closing, so `log.txt` can
 * show you if the engine is failing at some point.
 *
 * **NB:** remember to finish your log with `std::endl`.
 *
 * Example code:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
 *     MyEnt() : tank::Entity({0, 0})
 *     {
 *         Game::log << "Created MyEnt at position (0, 0)" << std::endl;
 *     }
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Example `log.txt`:
 *
 *     [00:00:00.231] Log file created
 *     [00:00:00.400] Opening Window
 *     [00:00:00.641] Loading main state
 *     [00:00:00.700] Loading World...
 *     [00:00:00.710] Created MyEnt at position (0, 0)
 *     [00:00:00.714] Entering main loop
 *     [00:00:33.227] Unloading World...
 *     [00:00:33.230] Closing Window
 *     [00:00:33.233] Closing log file
 *
 */
class Logger : public std::ostream
{
    std::string fileName_;
    Timer timer_;
    std::ofstream logFile_;
    Logger_buf buf_;

public:
    Logger(std::string file);
    void log(const std::string& s);
    ~Logger() throw();
};
}

#endif /* TANK_LOGGER_HPP */
