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

#include "Timer.hpp"

#include <sstream>
#include <thread>

namespace tank {

void Timer::start()
{
    startTick_ = std::chrono::steady_clock::now();

    started_ = true;
    paused_ = false;
}

void Timer::stop()
{
    started_ = false;
    paused_ = false;
}

void Timer::pause()
{
    if (started_ && not paused_)
    {
        pausedTick_ = std::chrono::steady_clock::now() - startTick_;
        paused_ = true;
    }
}

void Timer::resume()
{
    if (started_ && paused_)
    {
        paused_ = false;
        startTick_ = std::chrono::steady_clock::now() - pausedTick_;
    }
}

bool Timer::isStarted() const
{
    return started_;
}

bool Timer::isPaused() const
{
    return paused_;
}

std::chrono::steady_clock::duration Timer::getTicks() const
{
    if (not started_)
    {
        return std::chrono::steady_clock::duration::zero();
    }
    if (paused_)
    {
        return pausedTick_;
    }
    return std::chrono::steady_clock::now() - startTick_;
}

std::string Timer::getHumanTime() const
{
    long int millisecs =
        std::chrono::duration_cast<std::chrono::milliseconds>
        (getTicks()).count();
    // Returns time in H:M:S.uuuuuu
    std::stringstream s;
    s << millisecs/3600000 << ":" <<
            millisecs/60000 % 60 << ":" <<
            (millisecs % 60000)/1000.0;

    return s.str();
}

void Timer::delay(std::chrono::steady_clock::duration timeDelay)
{
    std::this_thread::sleep_for(timeDelay);
}

}
