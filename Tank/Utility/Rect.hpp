/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#ifndef TANK_RECT_HPP
#define TANK_RECT_HPP

namespace tank
{

/*!
 * \brief A templated rectangle stuct. Top left x,y then width and height.
 */
template <typename T>
struct Rect
{
    T x, y, w, h;
    Rect(T x = 0, T y = 0, T w = 0, T h = 0)
        : x(x) , y(y) , w(w) , h(h) {}
    template <typename U> Rect(U x, U y, U h, U w)
        : x(x) , y(y) , w(w) , h(h) {}
    template <typename U> Rect(const Rect<U>& rect)
        : x(rect.x) , y(rect.y) , w(rect.w) , h(rect.h) {}

};

template <typename T, typename U>
inline bool operator== (const Rect<T>& lhs, const Rect<U>& rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y and
           lhs.w == rhs.w and lhs.h == rhs.h;
}

template <typename T, typename U>
inline bool operator!= (const Rect<T>& lhs, const Rect<U>& rhs)
{
    return not operator==(lhs,rhs);
}

using Rectf = Rect<float>;
using Recti = Rect<int>;
using Rectu = Rect<unsigned int>;
using Rectd = Rect<double>;

}

#endif
