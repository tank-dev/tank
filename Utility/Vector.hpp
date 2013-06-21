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

#pragma once
#ifndef TANK_VECTOR_HPP
#define TANK_VECTOR_HPP

#include <cmath>

namespace tank {

template <typename T>
struct Vector
{
    T x, y;

	/*!
	 * \brief Performs the dot product of the vector and the input vector.
	 *
	 * \param b The vector to perfom the dot product with.
	 *
	 * \return The result of the dot product.
	 */
    inline T dot(Vector const& b) const
    {
        return x*b.x + y*b.y;
    }

	/*!
	 * \brief Calculates the length of the vector.
	 *
	 * \return The length of the vector.
	 */
    inline T magnitude() const
    {
        return sqrt(x*x+y*y);
    }

	/*!
	 * \brief Reterns a normalised vector.
	 *
	 * \return The normalised vector.
	 */
    inline Vector unit() const
    {
        const double mag = magnitude();
        return { x/mag,y/mag };
    }

	/*!
	 * \brief Multiplies the vector with a scalar
	 *
	 * \param f The scalar to multiply by.
	 *
	 * \return Returns a referance to itself.
	 */
    inline Vector& operator*=(T f)
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
    inline Vector& operator+=(Vector& vect)
    {
        x += vect.x;
        y += vect.y;

        return *this;
    }

	/*!
	 * \brief Adds a scalar times the vector (1, 1) to the vector.
	 *
	 * \param f The scalar to add.
	 *
	 * \return A reference to the vector.
	 */
    inline Vector& operator+=(T f)
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
    inline Vector& operator-=(Vector& vect)
    {
        x -= vect.x;
        y -= vect.y;

        return *this;
    }

	/*!
	 * \brief Subtracts a scalar times the vector (1, 1) to the vector.
	 *
	 * \param f The scalar to subtract.
	 *
	 * \return A reference to the vector.
	 */
    inline Vector& operator-=(T f)
    {
        x -= f;
        y -= f;

        return *this;
    }

	/*!
	 * \brief Checks if the vector is equal to another vector.
	 *
	 * \param vect The vector to check equality with.
	 *
	 * \return true if the vectors are equal.
	 */
    inline bool operator==(const Vector& vect) const
    {
        return x == vect.x && y == vect.y;
    }

	/*!
	 * \brief Multiplies a vector by a scalar.
	 *
	 * \param f The scalar to multiply by.
	 *
	 * \return The result of the multiplication.
	 */
    inline Vector operator*(T f) const
    {
        return { x*f, y*f };
    }

	/*!
	 * \brief Adds two vectors.
	 *
	 * \param b The other vector to add.
	 *
	 * \return The result of the addition.
	 */
    inline Vector operator+(Vector const& b) const
    {
        return {x+b.x, y+b.y};
    }

	/*!
	 * \brief Adds a vector and a scalar times the vector (1, 1).
	 *
	 * \param s The scalar to add.
	 *
	 * \return The result of the addition.
	 */
    inline Vector operator+(T s) const
    {
        return {x+s, y+s};
    }

	/*!
	 * \brief Subtacts a vector from another.
	 *
	 * \param b The vector to subtract.
	 *
	 * \return The result of the subtraction.
	 */
    inline Vector operator-(Vector const& b) const
    {
        return {x-b.x,y-b.y};
    }

	/*!
	 * \brief Subtracts a vector and a scalar times the vector (1, 1).
	 *
	 * \param s The scalar to subtract.
	 *
	 * \return The result of the subtraction.
	 */
    inline Vector operator-(T f) const
    {
        return {x-f,y-f};
    }
};

typedef Vector<float>  Vectorf;
typedef Vector<double> Vectord;
typedef Vector<int>    Vectori;

}

#endif
