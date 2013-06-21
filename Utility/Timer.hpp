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

/*
 * File:   Timer.hpp
 * Author: jamie & David W
 *
 * Created on 17 December 2011, 17:26
 */

#pragma once
#ifndef TANK_TIMER_HPP
#define TANK_TIMER_HPP

#include <chrono>
#include <cstring>
#include <string>

namespace tank {

class Timer
{
public:
    /*!
     * \brief Starts the timer
	 */
    void start();
    /*!
     * \brief Stops and resets the timer
	 */
    void stop();
    /*!
     * \brief Pauses the timer, maintains the current time on the timer.
	 */
    void pause();
    /*!
     * \brief Resumes the timer from where it left off.
	 */
    void resume();

    /*!
     * \brief Get where the timer has been started.
	 *
     * \return True if the timer has been started.
	 */
    bool isStarted();
    /*!
     * \brief Gets whether the timer is paused (NOTE: a stopped timer counts as paused.).
	 *
     * \return True if the timer is paused.
	 */
    bool isPaused();

    /*!
     * \brief Gets the number of milliseconds since the timer was started or 0
	 * if it hasn't been started.
	 *
     * \return The number of millisecnds since the timer was started.
	 */
    unsigned long getTicks();
    /*!
     * \brief Gets the number of microseconds since the timer was started or 0
	 * if it hasn't been started.
	 *
     * \return The number of microseconds since the timer was started.
	 */
	unsigned long getMicrosecs();

    /*!
     * \brief Get the time in a human readable format H:M:S.uuuuuu. Precision up to microseconds.
	 *
     * \return A string of the time, H:M:S.uuuuuu
	 */
	std::string getHumanTime();

    /*!
     * \brief Creates a timer object
	 */
    Timer();
    /*!
     * \brief Copies a timer.
	 *
     * \param orig The timer to copy.
	 */
    Timer(const Timer& orig);
    virtual ~Timer();

    /*!
     * \brief Delays the current thread for a numeber of milliseconds.
	 *
     * \param millisecs The number of milliseconds to delay the thread for.
	 */
    static void delay(unsigned long millisecs);
    /*!
     * \brief Delays the current thread for a numeber of microseconds. (NOTE:
	 * most computers may not have this sort of precision.)
	 *
     * \param microsecs The number of microseconds to delay the thread for.
	 */
    static void delayMicrosecs(unsigned long microsecs);
private:

	std::chrono::steady_clock::time_point startTick_;
	std::chrono::steady_clock::duration pausedTick_;
    bool started_;
    bool paused_;
};

}

#endif    /* TIMER_H */

