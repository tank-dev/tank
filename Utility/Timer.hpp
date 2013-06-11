/*
 * File:   Timer.hpp
 * Author: jamie & David W
 *
 * Created on 17 December 2011, 17:26
 */

#pragma once
#ifndef TIMER_H
#define    TIMER_H

#include <chrono>
#include <cstring>

class Timer
{
public:
    void start();
    void stop();
    void pause();
    void resume();

    static void delay(unsigned long microsecs);

    bool isStarted();
    bool isPaused();

    unsigned long getTicks();
	unsigned long getMicrosecs();

	std::string getHumanTime();

    Timer();
    Timer(const Timer& orig);
    virtual ~Timer();
private:

	std::chrono::steady_clock::time_point _startTick;
	std::chrono::steady_clock::duration _pausedTick;
    bool _started;
    bool _paused;
};

#endif    /* TIMER_H */

