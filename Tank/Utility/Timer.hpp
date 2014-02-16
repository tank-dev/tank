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

#ifndef TANK_TIMER_HPP
#define TANK_TIMER_HPP

#include <chrono>
#include <cstring>
#include <string>

namespace tank {

class Timer
{
    std::chrono::steady_clock::time_point startTick_;
    std::chrono::steady_clock::duration pausedTick_;
    bool started_ {false};
    bool paused_ {false};

public: 
    Timer() = default;
    Timer(const Timer& orig) = default;
    ~Timer() = default;

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
    bool isStarted() const;
    /*!
     * \brief Gets whether the timer is paused
     * (NOTE: a stopped timer counts as paused.).
     *
     * \return True if the timer is paused.
     */
    bool isPaused() const;

    /*!
     * \brief Gets the duration since the timer was started or 0 if it hasn't
     * been started.
     *
     * \return The chrono::steady_clock::duration since the timer was started.
     */
    std::chrono::steady_clock::duration getTicks() const;

    /*!
     * \brief Get the time in a human readable format H:M:S.uuuuuu.
     * Precision up to microseconds.
     *
     * \return A string of the time, H:M:S.uuuuuu
     */
    std::string getHumanTime() const;

    /*!
     * \brief Delays the current thread for a numeber of milliseconds.
     *
     * \param delayTime The chrono::steady_clock::duration to delay the thread for.
     */
    static void delay(std::chrono::steady_clock::duration timeDelay);
};

} // tank

#endif    /* TIMER_H */
