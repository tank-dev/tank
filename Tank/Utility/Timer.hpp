// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TIMER_HPP
#define TANK_TIMER_HPP

#include <chrono>
#include <cstring>
#include <string>

namespace tank
{

class Timer
{
    std::chrono::steady_clock::time_point startTick_;
    std::chrono::steady_clock::duration pausedTick_;
    bool started_{false};
    bool paused_{false};

public:
    Timer() = default;
    Timer(const Timer& orig) = default;
    ~Timer() = default;

    /*!
     * \brief Starts the timer
     */
    void start();
    /*!
     * \brief Stops and resets the timer
     */
    void stop();
    /*!
     * \brief Pauses the timer, maintains the current time on the timer.
     */
    void pause();
    /*!
     * \brief Resumes the timer from where it left off.
     */
    void resume();

    /*!
     * \brief This Offsets the timer back by the desired amount.
     *
     * \param change The duration to change the timer by.
     */
    void offset(std::chrono::milliseconds change);

    /*!
     * \brief Get where the timer has been started.
     *
     * \return True if the timer has been started.
     */
    bool isStarted() const;
    /*!
     * \brief Gets whether the timer is paused
     * (NOTE: a stopped timer counts as paused.).
     *
     * \return True if the timer is paused.
     */
    bool isPaused() const;

    /*!
     * \brief Gets the duration since the timer was started or 0 if it hasn't
     * been started.
     *
     * \return The chrono::steady_clock::duration since the timer was started.
     */
    std::chrono::steady_clock::duration getDuration() const;
    unsigned getTicks() const;

    /*!
     * \brief Get the time in a human readable format H:M:S.uuuuuu.
     * Precision up to microseconds.
     *
     * \return A string of the time, H:M:S.uuuuuu
     */
    std::string getHumanTime() const;

    /*!
     * \brief Delays the current thread for a numeber of milliseconds.
     *
     * \param delayTime The chrono::steady_clock::duration to delay the thread
     *for.
     */
    static void delay(std::chrono::steady_clock::duration timeDelay);
};

} // tank

#endif /* TIMER_H */
