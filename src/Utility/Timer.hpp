/*
 * File:   Timer.hpp
 * Author: jamie
 *
 * Created on 17 December 2011, 17:26
 */

#ifndef TIMER_H
#define	TIMER_H

#include <SDL/SDL_timer.h>

class Timer
{
public:
    void start();
    void stop();
    void pause();
    void resume();

    bool isStarted();
    bool isPaused();

    Uint32 getTicks();

    Timer();
    Timer(const Timer& orig);
    virtual ~Timer();
private:
    Uint32 _startTick;
    Uint32 _pausedTick;
    bool _started;
    bool _paused;
};

#endif	/* TIMER_H */

