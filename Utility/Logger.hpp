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

#pragma once
#ifndef TANK_LOGGER_HPP
#define TANK_LOGGER_HPP

#include "Timer.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace tank {

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
#ifdef DEBUG
            manip(std::clog);
#endif //DEBUG
            manip(enclosing_.logFile_);
            return *this;
        }
    } logHelper_{*this};

public:
	/*!
	 * \brief Creates a logger.
	 *
	 * \param file The name of the file to log to.
	 */
    Logger(std::string file);
    ~Logger();

	/*!
	 * \brief This acts like a stream to log comments. Remeber to end you
	 * comment with std::endl.
	 *
	 * \tparam T The type to comment, accepts all the same types as cerr and
	 * ofstream.
	 * \param t The comment to log.
	 *
	 * \return A reference to the class (in fact this isn't strictly true but
	 * that's all you need to know).
	 */
    template <typename T>
    LogHelper& operator<<(const T& t);
};

template <typename T>
Logger::LogHelper& Logger::operator<<(const T& t)
{
    logHelper_ << "["
        << fileName_
        << ": "
        << timer_.getHumanTime()
        << "] "
        << t;

    return logHelper_;
}

}

#endif //LOGGER_HPP
