/*
 * File:   Timer.cpp
 * Author: jamie
 *
 * Created on 17 December 2011, 17:26
 */

#include "Timer.hpp"

Timer::Timer()
{
    _startTick = 0;
    _pausedTick = 0;
    _started = false;
    _paused = false;
}

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
    _startTick = SDL_GetTicks();

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
    if(_started && !_paused) {
        _pausedTick = SDL_GetTicks() - _startTick;
        _paused = true;
    }
}

void Timer::resume()
{
    if(_started && _paused) {
        _paused = false;
    }
    _startTick = SDL_GetTicks() - _pausedTick;
}

bool Timer::isStarted()
{
    return _started;
}

bool Timer::isPaused()
{
    return _paused;
}

Uint32 Timer::getTicks()
{
    if(_paused) {
        return _pausedTick;
    }
    return SDL_GetTicks() - _startTick;
}
