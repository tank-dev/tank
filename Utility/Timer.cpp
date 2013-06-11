/*
 * File:   Timer.cpp
 * Author: jamie & David W
 *
 * Created on 17 December 2011, 17:26
 */

#include "Timer.hpp"
#include <thread>

Timer::Timer()
	: _startTick(),
	  _pausedTick(),
	  _started(false),
	  _paused(false) {}

Timer::Timer(const Timer& orig)
{
    _startTick = orig._startTick;
    _pausedTick = orig._pausedTick;
    _started = orig._started;
    _paused = orig._paused;
}

Timer::~Timer() {}

void Timer::start()
{
    _startTick = std::chrono::steady_clock::now();

    _started = true;
    _paused = false;
}

void Timer::stop()
{
    _started = false;
    _paused = false;
}

void Timer::pause()
{
    if(_started && !_paused)
    {
        _pausedTick = std::chrono::steady_clock::now() - _startTick;
        _paused = true;
    }
}

void Timer::resume()
{
    if(_started && _paused)
    {
        _paused = false;
		_startTick = std::chrono::steady_clock::now() - _pausedTick;
    }
}

bool Timer::isStarted()
{
    return _started;
}

bool Timer::isPaused()
{
    return _paused;
}

unsigned long Timer::getTicks()
{
    if(_paused)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds> (_pausedTick).count();
    }
    return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - _startTick).count();
}

void Timer::delay(unsigned long ms)
{
	std::chrono::milliseconds waitTime(ms);
	std::this_thread::sleep_for(waitTime);
}
