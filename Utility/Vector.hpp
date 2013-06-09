#pragma once
#ifndef VECTOR_H
#define    VECTOR_H

#include <cmath>

template <typename T>
struct Vector
{
    T x, y;

    inline T dot(Vector const& b) const
    {
        return x*b.x + y*b.y;
    }

    inline T magnitude() const
    {
        return sqrt(x*x+y*y);
    }

    inline Vector unit() const
    {
        const double mag = magnitude();
        return { x/mag,y/mag };
    }

    inline Vector& operator*=(float f)
    {
        x *= f;
        y *= f;

        return *this;
    }

    inline Vector& operator+=(Vector& vect)
    {
        x += vect.x;
        y += vect.y;

        return *this;
    }

    inline Vector& operator+=(float f)
    {
        x += f;
        y += f;

        return *this;
    }

    inline Vector& operator-=(Vector& vect)
    {
        x -= vect.x;
        y -= vect.y;

        return *this;
    }

    inline Vector& operator-=(T f)
    {
        x -= f;
        y -= f;

        return *this;
    }

    inline bool operator==(const Vector& vect) const
    {
        return x == vect.x && y == vect.y;
    }

    inline Vector operator*(float f) const
    {
        return { x*f, y*f };
    }
    inline Vector operator+(Vector const& b) const
    {
        return {x+b.x, y+b.y};
    }
    inline Vector operator+(T s) const
    {
        return {x+s, y+s};
    }
    inline Vector operator-(Vector const& b) const
    {
        return {x-b.x,y-b.y};
    }
    inline Vector operator-(T f) const
    {
        return {x-f,y-f};
    }
};

typedef Vector<float>  Vectorf; 
typedef Vector<double> Vectord; 
typedef Vector<int>    Vectori; 
#endif
