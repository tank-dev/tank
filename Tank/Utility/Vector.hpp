// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_VECTOR_HPP
#define TANK_VECTOR_HPP

#include <cmath>
#include <iostream>

namespace tank
{

template <typename T>
struct Vector
{
    T x, y;

    constexpr Vector(T x = 0, T y = 0) : x{x}, y{y}
    {
    }
    constexpr Vector(const Vector& vec) : x{vec.x}, y{vec.y}
    {
    }
    template <typename U>
    constexpr Vector(U x, U y)
            : x(x), y(y)
    {
    }
    template <typename U>
    constexpr Vector(const Vector<U>& vec)
            : x(vec.x), y(vec.y)
    {
    }

    /*!
     * \brief Performs the dot product of the vector and the input vector.
     *
     * \param b The vector to perfom the dot product with.
     *
     * \return The result of the dot product.
     */
    constexpr T dot(Vector const& b) const
    {
        return x * b.x + y * b.y;
    }

    /*!
     * \brief Calculates the length of the vector.
     *
     * \return The length of the vector.
     */
    constexpr T magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    /*!
     * \brief Calculates the length squared of the vector.
     *
     * This is slightly more efficient than calculating the length of the
     * vector. And for some algorithms this is all you need.
     *
     * \return The length squared of the vector.
     */
    constexpr T magnitudeSquared() const
    {
        return x * x + y * y;
    }

    Vector rotate(double angle) const
    {
        constexpr float toRad = 3.14159265 / 180;
        angle *= toRad;

        return {x * cos(angle) - y * sin(angle),
                y * cos(angle) + x * sin(angle)};
    }

    Vector rotateAbout(Vector p, double angle) const
    {
        Vector ans = *this - p;
        ans = ans.rotate(angle);
        return ans + p;
    }

    /*!
     * \brief Gets the signed angle in radians between the current vector and
     * the given vector.
     *
     * \param vec The vector to find the angle to.
     *
     * \return The angle between the vectors.
     */
    float getAngle(const Vector& vec) const
    {
        constexpr double radToDeg = 180 / 3.14159265;
        return radToDeg * std::atan2(x * vec.y - y * vec.x, dot(vec));
    }

    /*!
     * \brief Reterns a normalised vector.
     *
     * \return The normalised vector.
     */
    Vector unit() const
    {
        // TODO: this can be improved
        const T mag = magnitude();
        return {x / mag, y / mag};
    }

    constexpr Vector normal() const
    {
        return {-y, x};
    }

    /*!
     * \brief Multiplies the vector with a scalar
     *
     * \param f The scalar to multiply by.
     *
     * \return Returns a referance to itself.
     */
    template <typename U>
    Vector& operator*=(U const& f)
    {
        x *= f;
        y *= f;

        return *this;
    }

    /*!
     * \brief Divides the vector by a scalar
     *
     * \param f The scalar to divide by.
     *
     * \return Returns a referance to itself.
     */
    template <typename U>
    Vector& operator/=(U const& f)
    {
        x /= f;
        y /= f;

        return *this;
    }

    /*!
     * \brief Adds another vector to the vector.
     *
     * \param vect The vector to add.
     *
     * \return A reference to itself.
     */
    template <typename U>
    Vector& operator+=(Vector<U> const& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    /*!
     * \brief Adds a scalar times the vector (1, 1) to the vector.
     *
     * \param f The scalar to add.
     *
     * \return A reference to the vector.
     */
    template <typename U>
    Vector& operator+=(U const& f)
    {
        x += f;
        y += f;

        return *this;
    }

    /*!
     * \brief Subtracts a vector from the vector.
     *
     * \param vect The vector to subtract.
     *
     * \return A reference to the vector.
     */
    template <typename U>
    Vector& operator-=(Vector<U> const& vect)
    {
        x -= vect.x;
        y -= vect.y;

        return *this;
    }

    /*!
     * \brief Subtracts a scalar times the vector (1, 1) from the vector.
     *
     * \param f The scalar to subtract.
     *
     * \return A reference to the vector.
     */
    template <typename U>
    Vector& operator-=(U const& f)
    {
        x -= f;
        y -= f;

        return *this;
    }
};

template <typename T>
inline constexpr Vector<T> operator-(Vector<T> vec)
{
    return {-vec.x, -vec.y};
}

/*!
 * \brief Adds two vectors.
 *
 * \param b The other vector to add.
 *
 * \return The result of the addition.
 */
template <typename T, typename U>
constexpr inline auto operator+(const Vector<T>& lhs, const Vector<U>& rhs)
        -> Vector<decltype(lhs.x + rhs.x)>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

/*!
 * \brief Adds a vector and a scalar.
 *
 * \param s The scalar to add.
 *
 * \return The result of the addition.
 */
template <typename T, typename U>
constexpr inline auto operator+(const Vector<T>& lhs, const U& rhs)
        -> Vector<decltype(lhs.x + rhs)>
{
    return {lhs.x + rhs, lhs.y + rhs};
}

/*!
 * \brief Multiplies a vector by a scalar.
 *
 * \param f The scalar to add by.
 *
 * \return The result of the multiplication.
 */
template <typename T, typename U>
constexpr inline auto operator+(const T& lhs, const Vector<U>& rhs)
        -> Vector<decltype(lhs + rhs.x)>
{
    return {lhs + rhs.x, lhs + rhs.y};
}

/*!
 * \brief Subtacts a vector from another.
 *
 * \param b The vector to subtract.
 *
 * \return The result of the subtraction.
 */
template <typename T, typename U>
constexpr inline auto operator-(const Vector<T>& lhs, const Vector<U>& rhs)
        -> Vector<decltype(lhs.x - rhs.x)>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

/*!
 * \brief Subtracts a vector and a scalar times the vector (1, 1).
 *
 * \param s The scalar to subtract.
 *
 * \return The result of the subtraction.
 */
template <typename T, typename U>
constexpr inline auto operator-(const Vector<T>& lhs, const U& rhs)
        -> Vector<decltype(lhs.x - rhs)>
{
    return {lhs.x - rhs, lhs.y - rhs};
}

/*!
 * \brief Multiplies a vector by a scalar.
 *
 * \param f The scalar to subract from.
 *
 * \return The result of the multiplication.
 */
template <typename T, typename U>
constexpr inline auto operator-(const T& lhs, const Vector<U>& rhs)
        -> Vector<decltype(lhs - rhs.x)>
{
    return {lhs - rhs.x, lhs - rhs.y};
}

/*!
 * \brief Multiplies a vector by a scalar.
 *
 * \param f The scalar to multiply by.
 *
 * \return The result of the multiplication.
 */
template <typename T, typename U>
constexpr inline auto operator*(const Vector<T>& lhs, const U& rhs)
        -> Vector<decltype(lhs.x* rhs)>
{
    return {lhs.x * rhs, lhs.y * rhs};
}

/*!
 * \brief Multiplies a vector by a scalar.
 *
 * \param f The scalar to multiply by.
 *
 * \return The result of the multiplication.
 */
template <typename T, typename U>
constexpr inline auto operator*(const T& lhs, const Vector<U>& rhs)
        -> Vector<decltype(lhs* rhs.x)>
{
    return {lhs * rhs.x, lhs * rhs.y};
}

template <typename T, typename U>
constexpr inline auto operator/(const Vector<T>& lhs, const U& rhs)
        -> Vector<decltype(lhs.x / rhs)>
{
    return {lhs.x / rhs, lhs.y / rhs};
}

template <typename T, typename U>
inline auto operator/(const Vector<T>& lhs, const Vector<U>& rhs)
        -> Vector<decltype(lhs.x / rhs.x)>
{
    return {lhs.x / rhs.x, lhs.y / rhs.y};
}

/*!
 * \brief Checks if the vector is equal to another vector.
 *
 * \param vect The vector to check equality with.
 *
 * \return true if the vectors are equal.
 */
template <typename T, typename U>
constexpr inline bool operator==(const Vector<T>& lhs, const Vector<U>& rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y;
}

/*!
 * \brief Checks if the vector is not equal to another vector.
 *
 * \param vect The vector to check equality with.
 *
 * \return true if the vectors are not equal.
 */
template <typename T, typename U>
constexpr inline bool operator!=(const Vector<T>& lhs, const Vector<U>& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Vector<T> const& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

using Vectorf = Vector<float>;
using Vectord = Vector<double>;
using Vectori = Vector<int>;
using Vectoru = Vector<unsigned int>;

namespace literals
{
constexpr Vectorf operator""_x(long double x)
{
    return Vectorf(x, 0);
}

constexpr Vectorf operator""_y(long double y)
{
    return Vectorf(0, y);
}

constexpr Vectorf operator""_x(unsigned long long x)
{
    return Vectorf(x, 0);
}

constexpr Vectorf operator""_y(unsigned long long y)
{
    return Vectorf(0, y);
}

constexpr Vectord operator""_xd(long double x)
{
    return Vectord(x, 0);
}

constexpr Vectord operator""_yd(long double y)
{
    return Vectord(0, y);
}

constexpr Vectori operator""_xi(unsigned long long x)
{
    return Vectori(x, 0);
}

constexpr Vectori operator""_yi(unsigned long long y)
{
    return Vectori(0, y);
}

constexpr Vectoru operator""_xu(unsigned long long x)
{
    return Vectori(x, 0);
}

constexpr Vectoru operator""_yu(unsigned long long y)
{
    return Vectoru(0, y);
}
}
}

namespace std
{
template <typename T>
struct hash<tank::Vector<T>>
{
    using argument_type = tank::Vector<T>;
    using value_type = std::size_t;

    constexpr value_type operator()(const argument_type& v) const
    {
        return std::hash<T>()(v.x) ^ (std::hash<T>()(v.y) << 1);
    }
};
}

#endif
