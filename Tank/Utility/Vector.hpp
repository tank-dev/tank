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

#ifndef TANK_VECTOR_HPP
#define TANK_VECTOR_HPP

#include <cmath>

namespace tank
{

template <typename T>
struct Vector
{
    T x, y;

    Vector(T x = 0, T y = 0) : x{x}, y{y} {}
    Vector(const Vector& vec) : x{vec.x}, y{vec.y} {}
    template <typename U> Vector(U x, U y) : x(x), y(y) {}
    template <typename U> Vector(const Vector<U>& vec) : x(vec.x), y(vec.y) {}

    /*!
     * \brief Performs the dot product of the vector and the input vector.
     *
     * \param b The vector to perfom the dot product with.
     *
     * \return The result of the dot product.
     */
    T dot(Vector const& b) const
    {
        return x*b.x + y*b.y;
    }

    /*!
     * \brief Calculates the length of the vector.
     *
     * \return The length of the vector.
     */
    T magnitude() const
    {
        return sqrt(x*x+y*y);
    }

    /*!
     * \brief Calculates the length squared of the vector.
	 *
	 * This is slightly more efficient than calculating the length of the
	 * vector. And for some algorithms this is all you need.
     *
     * \return The length squared of the vector.
     */
	T magnitudeSquared() const
	{
		return x*x + y*y;
	}

    Vector rotate(double angle) const
    {
        constexpr float toRad = 3.14159265 / 180;
        angle *= toRad;

        return {
            x * cos(angle) + y * sin(angle),
            y * cos(angle) - x * sin(angle)
        };
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
		return std::atan2(x * vec.y - y * vec.x, dot(vec));
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
        return {x/mag, y/mag};
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

/*!
 * \brief Adds two vectors.
 *
 * \param b The other vector to add.
 *
 * \return The result of the addition.
 */
template <typename T, typename U>
inline auto operator+ (const Vector<T>& lhs, const Vector<U>& rhs) ->
                                                Vector<decltype(lhs.x + rhs.x)>
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
inline auto operator+ (const Vector<T>& lhs, const U& rhs) ->
                                                Vector<decltype(lhs.x + rhs)>
{
    return {lhs.x + rhs, lhs.y + rhs};
}

/*!
 * \brief Subtacts a vector from another.
 *
 * \param b The vector to subtract.
 *
 * \return The result of the subtraction.
 */
template <typename T, typename U>
inline auto operator- (const Vector<T>& lhs, const Vector<U>& rhs) ->
                                                Vector<decltype(lhs.x - rhs.x)>
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
 inline auto operator- (const Vector<T>& lhs, const U& rhs) ->
                                                Vector<decltype(lhs.x - rhs)>
{
    return {lhs.x - rhs, lhs.y - rhs};
}

/*!
 * \brief Multiplies a vector by a scalar.
 *
 * \param f The scalar to multiply by.
 *
 * \return The result of the multiplication.
 */
template <typename T, typename U>
inline auto operator* (const Vector<T>& lhs, const U& rhs) ->
                                                Vector<decltype(lhs.x * rhs)>
{
    return {lhs.x * rhs, lhs.y * rhs};
}

template <typename T, typename U>
inline auto operator/ (const Vector<T>& lhs, const U& rhs) ->
                                                Vector<decltype(lhs.x / rhs)>
{
    return {lhs.x / rhs, lhs.y / rhs};
}

/*!
 * \brief Checks if the vector is equal to another vector.
 *
 * \param vect The vector to check equality with.
 *
 * \return true if the vectors are equal.
 */
template <typename T, typename U>
inline bool operator== (const Vector<T>& lhs, const Vector<U>& rhs)
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
inline bool operator!= (const Vector<T>& lhs, const Vector<U>& rhs)
{
    return not operator==(lhs, rhs);
}

using Vectorf = Vector<float>;
using Vectord = Vector<double>;
using Vectori = Vector<int>;
using Vectoru = Vector<unsigned int>;

}

#endif
