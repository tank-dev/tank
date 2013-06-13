/*
 * File:   Timer.cpp
 * Author: jamie & David W
 *
 * Created on 17 December 2011, 17:26
 */

#include "Timer.hpp"
#include <thread>

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
    if(started_ && !paused_)
    {
        pausedTick_ = std::chrono::steady_clock::now() - startTick_;
        paused_ = true;
    }
}

void Timer::resume()
{
    if(started_ && paused_)
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
	if (!started_)
   	{
		return 0;
	}
    if(paused_)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds> (pausedTick_).count();
    }
    return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - startTick_).count();
}

unsigned long Timer::getMicrosecs()
{
	if (!started_)
   	{
		return 0;
	}
    if(paused_)
    {
        return std::chrono::duration_cast<std::chrono::microseconds> (pausedTick_).count();
    }
    return std::chrono::duration_cast<std::chrono::microseconds> (std::chrono::steady_clock::now() - startTick_).count();
}

std::string Timer::getHumanTime()
{
	long int microsecs = getMicrosecs();
	// Returns time in H:M:S.uuuuuu
	return std::to_string(microsecs/3600000000) + ":" + std::to_string(microsecs/60000000 % 60) + ":" + std::to_string((microsecs % 60000000)/1000000.0 );
}

void Timer::delay(unsigned long microsecs)
{
	std::chrono::microseconds waitTime(microsecs);
	std::this_thread::sleep_for(waitTime);
}
