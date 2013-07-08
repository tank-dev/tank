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
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
#include <windows.h>
#else
#include <thread>
#endif

namespace tank
{

Timer::Timer()
    : startTick_(),
      pausedTick_(),
      started_(false),
      paused_(false) {}

Timer::Timer(const Timer& orig)
{
    startTick_ = orig.startTick_;
    pausedTick_ = orig.pausedTick_;
    started_ = orig.started_;
    paused_ = orig.paused_;
}

Timer::~Timer() {}

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

bool Timer::isStarted()
{
    return started_;
}

bool Timer::isPaused()
{
    return paused_;
}

unsigned long Timer::getTicks()
{
    if (not started_)
    {
        return 0;
    }
    if (paused_)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>
                (pausedTick_).count();
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::steady_clock::now() - startTick_).count();
}

unsigned long Timer::getMicrosecs()
{
    if (not started_)
    {
        return 0;
    }
    if (paused_)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>
                (pausedTick_).count();
    }
    return std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::steady_clock::now() - startTick_).count();
}

std::string Timer::getHumanTime()
{
    long int microsecs = getMicrosecs();
    // Returns time in H:M:S.uuuuuu
    std::stringstream s;
    s << microsecs/3600000000 << ":" <<
            microsecs/60000000 % 60 << ":" <<
            (microsecs % 60000000)/1000000.0;

    return s.str();
}

void Timer::delay(unsigned long millisecs)
{
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
	Sleep(millisecs);
#else
    std::chrono::milliseconds waitTime(millisecs);
    std::this_thread::sleep_for(waitTime);
#endif
}

void Timer::delayMicrosecs(unsigned long microsecs)
{
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
	Sleep(microsecs / 1000);
#else
    std::chrono::microseconds waitTime(microsecs);
    std::this_thread::sleep_for(waitTime);
#endif
}

}
