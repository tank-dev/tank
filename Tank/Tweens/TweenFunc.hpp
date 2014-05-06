// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TWEENFUNC_HPP
#define TANK_TWEENFUNC_HPP

#include <chrono>
#include <functional>

namespace tank 
{

template<typename T>
class Tween;

/*!
 * \brief This is a template class for the tween functions.
 *
 * Writing A Tween Function
 * ========================
 *
 * Firstly it goes without saying that you must public inherit from TweenFunc.
 * I will go through the function that need to be overloading in the order that
 * the will be used.
 * 
 * The constructor
 * ---------------
 *
 *  This works just as you would expect, although a start value for the
 *  function is not provided.
 *
 * Getting the initial value
 * -------------------------
 *  
 *  The initial value of the function is provided by `setValue(T)`
 *
 *  At this point `offset()` is called with how much time the previous function
 *  overran. You should adjust you function accordingly to avoid stutter. If
 *  you are using the Timer class the function `Timer::offset()` is designed
 *  with this in mind.
 *
 * Pausing and Resuming
 * --------------------
 *
 *  Your function may need to be paused and resumed. Again if you are using
 *  Timer then `Timer::pause()` and `Timer::resume()` there are designed for
 *  this.
 *
 * Getting the value
 * -----------------
 *
 *  `getValue()` is arguably the most coplicated step. You should check to see
 *  if the function has finished. If it has calculate how much time the
 *  function has overran and return
 *
 *      return TweenFunc<T>::end(overrun);
 *
 *  This will set up the next tween function and return the correct value from
 *  that. Otherwise just calculate the value of the tween.
 *
 * Get Last Value
 * --------------
 *
 *  `getLastValue()` should return the value when the tween finishes. It is
 *  called after the tween has finished when setting up the next tween.
 *
 * \tparam T The type that the tween function operates on.
 */
template<typename T>
class TweenFunc
{
    std::function<T(std::chrono::milliseconds const&)> finishedCallback_;

    /*!
     * \brief This sets up a tween function and so needs access to do it.
     */
    friend Tween<T>::Tween(T const& intialValue);

    /*!
     * \brief This is the function that set's up the tween functions, it need
     * access to do that.
     */
    template<typename S, typename... Args>
    friend void Tween<T>::useWithValue(T const& value, Args... args);

    /*!
     * \brief This sets the callback that the tween calles when it finishes.
     *
     * \param finishedCallback The callback.
     */
    void setCallback(std::function<T(std::chrono::milliseconds const&)> finishedCallback);

protected:
    /*!
     * \brief This should be called when the tween ends.
     *
     * \param overrun The amount that the tween has overran.
     *
     * \return The value of the new tween set.
     */
    T end(std::chrono::milliseconds const& overrun) const;
    /*!
     * \brief This is to set the initial value of the tween, it is called when
     * the tween is initialised.
     *
     * \param T the inital value of the tween
     */
    virtual void setValue(T) = 0;
    
public:
    TweenFunc() = default;

    /*!
     * \brief Gets the current value of the tween
     *
     * \return The current value of the tween
     */
    virtual T getValue() const = 0;

    /*!
     * \brief Gets the last posible value of the tween
     *
     * \return The last possible value of the tween
     */
    virtual T getLastValue() const = 0;

    /*!
     * \brief This pauses the tween
     */
    virtual void pause() = 0;
    /*!
     * \brief This resumes the tween after pausing
     */
    virtual void resume() = 0;

    /*!
     * \brief This offsets the tween by the designated ammount
     */
    virtual void offset(std::chrono::milliseconds const& delay) = 0;
};

template<typename T>
void TweenFunc<T>::setCallback(std::function<T(std::chrono::milliseconds const&)> finishedCallback)
{
    finishedCallback_ = finishedCallback;
}

template<typename T>
T TweenFunc<T>::end(std::chrono::milliseconds const& overrun) const
{
    return finishedCallback_(overrun);
}

} // tank

#endif // TANK_TWEENFUNC_HPP
