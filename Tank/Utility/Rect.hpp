// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_RECT_HPP
#define TANK_RECT_HPP

#include "Vector.hpp"

namespace tank
{

/*!
 * \brief A templated rectangle stuct. Top left x,y then width and height.
 */
template <typename T>
struct Rect
{
    T x, y, w, h;
    constexpr Rect(T x = 0, T y = 0, T w = 0, T h = 0)
        : x(x) , y(y) , w(w) , h(h) {}
    template <typename U> constexpr Rect(U x, U y, U h, U w)
        : x(x) , y(y) , w(w) , h(h) {}
    template <typename U> constexpr Rect(const Rect<U>& rect)
        : x(rect.x) , y(rect.y) , w(rect.w) , h(rect.h) {}

    template<typename U>
    bool intersects(Rect<U> const& rect) const
    {
        if (rect.x + rect.w < x or
            rect.y + rect.h < y or
            rect.x > x + w or
            rect.y > x + h)
        {
            return false;
        }
        return true;
    }

    template<typename U>
    bool intersects(Vector<U> const& point) const
    {
        if (point.x < x or point.x > x + w or point.y < y or point.y > y + h)
        {
            return false;
        }
        return true;
    }
};

template <typename T, typename U>
constexpr inline bool operator== (const Rect<T>& lhs, const Rect<U>& rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y and
           lhs.w == rhs.w and lhs.h == rhs.h;
}

template <typename T, typename U>
constexpr inline bool operator!= (const Rect<T>& lhs, const Rect<U>& rhs)
{
    return not operator==(lhs,rhs);
}

using Rectf = Rect<float>;
using Recti = Rect<int>;
using Rectu = Rect<unsigned int>;
using Rectd = Rect<double>;

}

#endif
