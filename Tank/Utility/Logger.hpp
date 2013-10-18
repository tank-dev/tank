/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

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
