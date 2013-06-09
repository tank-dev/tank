/*
 * File:   Timer.cpp
 * Author: jamie
 *
 * Created on 17 December 2011, 17:26
 */

#include "Timer.hpp"

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

#include <windows.h>

#else  /* presume POSIX */

#include <unistd.h>

#endif

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
    if(_started && !_paused)
    {
        _pausedTick = SDL_GetTicks() - _startTick;
        _paused = true;
    }
}

void Timer::resume()
{
    if(_started && _paused)
    {
        _paused = false;
    }
    _startTick = SDL_GetTicks() - _pausedTick;
}


#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

void Timer::delay( unsigned long ms )
{
    Sleep( ms );
}

#else  /* presume POSIX */

void Timer::delay( unsigned long ms )
{
    usleep( ms * 1000 );
}

#endif

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
    if(_paused)
    {
        return _pausedTick;
    }
    return SDL_GetTicks() - _startTick;
}
