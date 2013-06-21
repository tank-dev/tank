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
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson
 */

#include "Logger.hpp"

namespace tank {

Logger::Logger(std::string file) : fileName_{file}, logFile_{fileName_}
{
    timer_.start();
    logFile_ << "["
        << file
        << ": "
        << timer_.getHumanTime()
        << "] "
        << "Log file created..."
        << std::endl;
#ifdef DEBUG
    std::clog << "["
        << file
        << ": "
        << timer_.getHumanTime()
        << "] "
        << "Log file created..."
        << std::endl;
#endif
}

Logger::~Logger()
{
    logHelper_ << '\n';
}

}
