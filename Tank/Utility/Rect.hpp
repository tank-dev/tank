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
struct Rect {
    //! \brief x coordinate of the top left point of the rectangle.
    T x;

    //! \brief y coordinate of the top left point of the rectangle.
    T y;

    //! \brief width of the rectangle.
    T w;

    //! \brief height of the rectangle.
    T h;

    /*! \brief Construct a rectangle with the given values.
     *
     * Defaults to an empty rectangle.
     */
    constexpr Rect(T x = 0, T y = 0, T w = 0, T h = 0) : x{x}, y{y}, w{w}, h{h}
    {
    }

    /*! \brief Construct a rectangle with the given values, convertible to T.
     *
     * Implicitly converts the parameters to the type of the rectangle.
     */
    template <typename U>
    constexpr Rect(U x, U y, U w, U h) : x(x), y(y), w(w), h(h)
    {
    }

    /*! \brief Copy constructor.
     *
     * This works for a rectangle of any type U that is convertible to T.
     */
    template <typename U>
    constexpr Rect(const Rect<U>& rect)
        : x(rect.x), y(rect.y), w(rect.w), h(rect.h)
    {
    }

    /*! \brief Calculate intersection of two rectangles.
     *
     * \returns Whether the rectangles intersect.
     */
    template <typename U>
    bool intersects(Rect<U> const& rect) const
    {
        return !(rect.x + rect.w < x || rect.y + rect.h < y ||
                 rect.x > x + y || rect.y > x + h);
    }

    /*! \brief Calculate intersection of rectangle and point.
     *
     * \returns Whether the point is inside the rectangle or not.
     */
    template <typename U>
    bool intersects(Vector<U> const& point) const
    {
        return !(point.x < x || point.x > x + w ||
                 point.y < y || point.y > y + h);
    }
};

/*! \brief Equality comparison for Rects
 *
 * This will work for any two rects of comparable types.
 *
 * \relates Rect
 */
template <typename T, typename U>
constexpr inline bool operator==(const Rect<T>& lhs, const Rect<U>& rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y and lhs.w == rhs.w and
        lhs.h == rhs.h;
}

/*! \brief Inequality comparison for Rects
 *
 * This will work for any two rects of comparable types.
 *
 * \relates Rect
 */
template <typename T, typename U>
constexpr inline bool operator!=(const Rect<T>& lhs, const Rect<U>& rhs)
{
    return !operator==(lhs, rhs);
}


/*! \brief Rectangle of floats.
 */
using Rectf = Rect<float>;

/*! \brief Rectangle of signed integers.
 */
using Recti = Rect<int>;

/*! \brief Rectangle of unsigned integers.
 */
using Rectu = Rect<unsigned int>;

/*! \brief Rectangle of doubles.
 */
using Rectd = Rect<double>;
}

#endif
