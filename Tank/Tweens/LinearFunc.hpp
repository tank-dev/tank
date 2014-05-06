// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_LINEARFUNC_HPP
#define TANK_LINEARFUNC_HPP

#include "TweenFunc.hpp"
#include "../Utility/Timer.hpp"

#include <chrono>
#include <functional>

namespace tank 
{

template<typename T>
class LinearFunc final : public TweenFunc<T>
{
    T value_;
    T target_;
    std::chrono::milliseconds duration_;
    Timer timer_;

protected:    
    virtual void setValue(T value);

public:
    LinearFunc(T const& target, std::chrono::milliseconds const& duration);

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
    virtual void offset(std::chrono::milliseconds const& delay) override;
};

template<typename T>
LinearFunc<T>::LinearFunc(T const& target, std::chrono::milliseconds const& duration)
    : target_(target)
    , duration_(duration)
{
    timer_.start();
}

template<typename T>
T LinearFunc<T>::getValue() const
{
    std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(timer_.getTicks());
    if (duration_ > currentTime)
    {
        return value_ + currentTime.count() * (target_ - value_) / duration_.count();
    }
    else
    {
        return TweenFunc<T>::end(currentTime - duration_);
    }
}

template<typename T>
T LinearFunc<T>::getLastValue() const
{
    return target_;
}

template<typename T>
void LinearFunc<T>::pause()
{
    timer_.pause();
}

template<typename T>
void LinearFunc<T>::resume()
{
    timer_.resume();
}

template<typename T>
void LinearFunc<T>::offset(std::chrono::milliseconds const& delay)
{
    timer_.offset(delay);
}

template<typename T>
void LinearFunc<T>::setValue(T value)
{
    value_ = value;
}

} // tank

#endif // TANK_LINEARFUNC_HPP
