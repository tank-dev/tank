// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TWEEN_HPP
#define TANK_TWEEN_HPP

#include "TweenFunc.hpp"
#include "SteadyFunc.hpp"

#include <chrono>
#include <functional>
#include <memory>

namespace tank 
{

template<typename T>
class Tween
{
    /*!
     * \brief The tween function that is currently being used.
     */
    std::unique_ptr<TweenFunc<T>> tweenFunction_;
    /*!
     * \brief The callback to set up a new tween function.
     */
    std::function<void()> callback_ = []() {};

    /*!
     * \brief This stores whether we are currently at the end of a Tween. This
     * will be used to stop the infinite loop
     *
     * getValue -> tweenEnd -> callback_ -> use -> getValue -> ...
     */
    bool inberTween_ = false;

    /*!
     * \brief This is called when the tween function ends and sets up the new
     * tween fuction.
     *
     * \param overrun The amount the last tween function overran.
     *
     * \return The value of the newly set up tween.
     */
    T tweenEnd(std::chrono::milliseconds const& overrun);

    /*!
     * \brief This sets the tween funciton `S` to be used, with value
     * specified.
     *
     * \tparam S The classname of the tween function to be used.
     * \param value The value to start the tween function at.
     * \param args The arguments to set up the tween function.
     */
    template<typename S, typename... Args>
    void useWithValue(T const& value, Args... args);
public:
    Tween(T const& initalValue);

    /*!
     * \brief This set the tween function `S` to be used, continuing from the
     * value of the last tween.
     *
     * \tparam S The classname of the tween function to be used.
     * \param args The arguments to set up the tween function.
     */
    template<typename S, typename... Args>
    void use(Args... args);

    /*!
     * \brief This makes the tween the Steady tween with the specified value.
     *
     * \param value The value to set.
     */
    void setValue(T const& value);
    /*!
     * \brief This gets the current value of the tween, if the tween is
     * finished it will call the callback function to get a new tween.
     *
     * \return The current value of the tween.
     */
    T getValue();

    /*!
     * \brief This sets the callback function for when the tween function
     * finishes.
     *
     * \param callback The callback function.
     */
    void setCallback(std::function<void()> callback);

    /*!
     * \brief This stops the tween, (in fact it replaces the tween with the
     * steady tween). It is equivalent to
     *     use<SteadyFunc>();
     */
    void stop();
    /*!
     * \brief This pauses the tween
     */
    void pause();
    /*!
     * \brief This resumes a paused tween
     */
    void resume();
};

template<typename T>
Tween<T>::Tween(T const& initalValue)
    : tweenFunction_{new SteadyFunc<T>()}
{
    tweenFunction_->setValue(initalValue);
    tweenFunction_->setCallback([this](std::chrono::milliseconds const& overrun) -> T {
            return tweenEnd(overrun);
            });
}

template<typename T>
T Tween<T>::tweenEnd(std::chrono::milliseconds const& overrun)
{
    inberTween_ = true;
    // We get the last value of our tween function to use as our initial value.
    callback_();
    // We check if we have attached a new tween function
    if (inberTween_)
    {
        // We haven't attached a new tween funciton, so add a steady tween
        // function.
        useWithValue<SteadyFunc<T>>(tweenFunction_->getLastValue());
    }
    else
    {
        // We offset the tween to avoid stuttering
        tweenFunction_->offset(overrun);
    }
    return tweenFunction_->getValue();
}

template<typename T>
template<typename S, typename... Args>
void Tween<T>::useWithValue(T const& value, Args... args)
{
    static_assert(std::is_base_of<TweenFunc<T>, S>::value,
                  "Type must derive from TweenFunc<T>");
    static_assert(std::is_convertible<S*, TweenFunc<T>*>::value,
                  "Type must derive publically from TweenFunc<T>");

    tweenFunction_.reset(new S(std::forward<Args>(args)...));
    tweenFunction_->setValue(value);
    tweenFunction_->setCallback([this](std::chrono::milliseconds const& overrun) -> T {
            return tweenEnd(overrun);
            });
    inberTween_ = false;
}

template<typename T>
template<typename S, typename... Args>
void Tween<T>::use(Args... args)
{
    if (inberTween_)
    {
        useWithValue<S>(tweenFunction_->getLastValue(), std::forward<Args>(args)...);
    }
    else
    {
        useWithValue<S>(tweenFunction_->getValue(), std::forward<Args>(args)...);
    }
}

template<typename T>
void Tween<T>::setValue(T const& value)
{
    useWithValue<SteadyFunc>(value);
}

template<typename T>
T Tween<T>::getValue()
{
    return tweenFunction_->getValue();
}

template<typename T>
void Tween<T>::setCallback(std::function<void()> callback)
{
    callback_ = callback;
}

template<typename T>
void Tween<T>::stop()
{
    use<SteadyFunc>();
}

template<typename T>
void Tween<T>::pause()
{
    tweenFunction_->pause();
}

template<typename T>
void Tween<T>::resume()
{
    tweenFunction_->resume();
}

} // tank

#endif // TANK_TWEEN_HPP
