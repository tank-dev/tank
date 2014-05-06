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

template<typename T>
class TweenFunc
{
    std::function<T(std::chrono::milliseconds const&)> finishedCallback_;

    friend Tween<T>::Tween(T const& intialValue);

    template<typename S, typename... Args>
    friend void Tween<T>::useWithValue(T const& value, Args... args);

    void setCallback(std::function<T(std::chrono::milliseconds const&)> finishedCallback);

protected:
    void end(std::chrono::milliseconds const& overrun);
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
    virtual void offset(std::chrono::microseconds delay) = 0;
};

template<typename T>
void TweenFunc<T>::setCallback(std::function<T(std::chrono::milliseconds const&)> finishedCallback)
{
    finishedCallback_ = finishedCallback;
}

template<typename T>
void TweenFunc<T>::end(std::chrono::milliseconds const& overrun)
{
    finishedCallback_(getLastValue(), overrun);
}

} // tank

#endif // TANK_TWEENFUNC_HPP
