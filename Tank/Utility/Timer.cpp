// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

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

void Timer::offset(std::chrono::milliseconds change)
{
    if (started_ && not paused_)
    {
        startTick_ -= change;
    }
    else if (paused_)
    {
        // The paused tick is an offset backwards already
        pausedTick_ += change;
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
