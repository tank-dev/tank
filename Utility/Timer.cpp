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

unsigned long Timer::getMicrosecs()
{
    if(_paused)
    {
        return std::chrono::duration_cast<std::chrono::microseconds> (_pausedTick).count();
    }
    return std::chrono::duration_cast<std::chrono::microseconds> (std::chrono::steady_clock::now() - _startTick).count();
}

std::string Timer::getHumanTime()
{
	long int microsecs = getMicrosecs();
	// Returns time in HH:MM:SS.uuuuuu
	return std::to_string(microsecs/3600000000) + ":" + std::to_string(microsecs/60000000 % 60) + ":" + std::to_string((microsecs % 60000000)/1000000.0 );
}

void Timer::delay(unsigned long microsecs)
{
	std::chrono::microseconds waitTime(microsecs);
	std::this_thread::sleep_for(waitTime);
}
