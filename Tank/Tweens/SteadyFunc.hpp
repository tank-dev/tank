// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_STEADYFUNC_HPP
#define TANK_STEADYFUNC_HPP

#include "TweenFunc.hpp"

#include <chrono>
#include <functional>

namespace tank 
{

template<typename T>
class SteadyFunc final : public TweenFunc<T>
{
    T value_;
protected:    
    virtual void setValue(T value);
public:
    SteadyFunc() = default;

    /*!
     * \brief Gets the current value of the tween
     *
     * \return The current value of the tween
     */
    virtual T getValue() const override;
    /*!
     * \brief Gets the last value of the tween
     *
     * \return The last value of the tween
     */
    virtual T getLastValue() const override;

    /*!
     * \brief This pauses the tween
     */
    virtual void pause() override;
    /*!
     * \brief This resumes the tween after pausing
     */
    virtual void resume() override;

    /*!
     * \brief This offsets the tween by the designated ammount
     */
    virtual void offset(std::chrono::microseconds delay) override;
};

template<typename T>
T SteadyFunc<T>::getValue() const
{
    return value_;
}

template<typename T>
T SteadyFunc<T>::getLastValue() const
{
    return value_;
}

template<typename T>
void SteadyFunc<T>::pause()
{}

template<typename T>
void SteadyFunc<T>::resume()
{}

template<typename T>
void SteadyFunc<T>::offset(std::chrono::microseconds delay)
{}

template<typename T>
void SteadyFunc<T>::setValue(T value)
{
    value_ = value;
}

} // tank

#endif // TANK_STEADYFUNC_HPP
