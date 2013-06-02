#pragma once
#ifndef VECTOR_H
#define	VECTOR_H

#include <cmath>

struct Vector
{
    double x, y;
    
    double Magnitude()
    {
        return sqrt(x*x+y*y);
    }
    
    Vector Versor()
    {
        const double mag = Magnitude();
        return { x/mag,y/mag };
    }
    
    Vector& operator*=(float f)
    {
        x *= f;
        y *= f;
        
        return *this;
    }
    
    Vector& operator+=(Vector &vect)
    {
        x += vect.x;
        y += vect.y;
        
        return *this;
    }
    
    Vector& operator+=(float f)
    {
        x += f;
        y += f;
        
        return *this;
    }
    
    Vector& operator-=(Vector &vect)
    {
        x -= vect.x;
        y -= vect.y;
        
        return *this;
    }
    
    Vector& operator-=(float f)
    {
        x -= f;
        y -= f;
        
        return *this;
    }
    
    bool operator==(const Vector &vect)
    {
        return x == vect.x && y == vect.y;
    }
    
    friend float  operator*(Vector const& a, Vector const& b);
    friend Vector operator*(Vector const& vect, float f);
    friend Vector operator+(Vector const& a, Vector const& b);
    friend Vector operator+(Vector const& vect, float f);
    friend Vector operator+(float f, Vector const& vect);
    friend Vector operator-(Vector const& a, Vector const& b);
    friend Vector operator-(Vector const& vect, float f);
    friend Vector operator-(float f, Vector const& vect);
}; 
#endif
