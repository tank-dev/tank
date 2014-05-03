// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_GRID_HPP
#define TANK_GRID_HPP

#include <vector>
#include "Vector.hpp"
#include "Rect.hpp"

namespace tank
{

template<typename T>
class Grid
{
    std::vector<T> data;
    Vectoru dimensions;

public:
    Grid(const Vectoru& dims);
    Grid(const Vectoru& dims, T intialValue);

    T& operator[](const Vectoru& location);
    const T& operator[](const Vectoru& location) const;

    T& at(const Vectoru& location);
    const T& at(const Vectoru& location) const;

    unsigned getWidth() const
    {
        return dimensions.x;
    }

    unsigned getHeight() const
    {
        return dimensions.y;
    }

    const Vectoru& getDimensions() const
    {
        return dimensions;
    }
};

} // namespace tank

#endif // TANK_GRID_HPP
