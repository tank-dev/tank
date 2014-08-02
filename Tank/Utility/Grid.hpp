// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_GRID_HPP
#define TANK_GRID_HPP

#include <vector>
#include "Vector.hpp"
#include "Rect.hpp"

#include <stdexcept>

namespace tank
{

/*!
 * /brief This store a grid
 */
template <typename T>
class Grid
{
    std::vector<T> data;
    Vectoru dimensions{0, 0};

public:
    Grid() = default;
    Grid(const Vectoru& dims);
    Grid(const Vectoru& dims, T intialValue);

    using ref = typename std::vector<T>::reference;
    using const_ref = typename std::vector<T>::const_reference;

    ref operator[](const Vectoru& location)
    {
        return data[dimensions.x * location.y + location.x];
    }
    const_ref operator[](const Vectoru& location) const
    {
        return data[dimensions.x * location.y + location.x];
    }

    ref operator[](size_t pos)
    {
        return data[pos];
    }
    const_ref operator[](size_t pos) const
    {
        return data[pos];
    }

    ref at(const Vectoru& location)
    {
        if (location.x < dimensions.x and location.y < dimensions.y) {
            return data[dimensions.x * location.y + location.x];
        } else {
            throw std::out_of_range("Invalid Argument");
        }
    }
    const_ref at(const Vectoru& location) const
    {
        if (location.x < dimensions.x and location.y < dimensions.y) {
            return data[dimensions.x * location.y + location.x];
        } else {
            throw std::out_of_range("Invalid Argument");
        }
    }

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

    void setLine(const Vectoru& start, const Vectoru& end, T value);
    void fillBox(const Vectoru& start, const Vectoru& end, T value);
    void outlineBox(const Vectoru& start, const Vectoru& end, T value);
};

template <typename T>
Grid<T>::Grid(const Vectoru& dims)
        : data(dims.x * dims.y), dimensions(dims)
{
}

template <typename T>
Grid<T>::Grid(const Vectoru& dims, T intialValue)
        : data(dims.x * dims.y, intialValue), dimensions(dims)
{
}

template <typename T>
void Grid<T>::setLine(const Vectoru& start, const Vectoru& end, T value)
{
    // This uses Bresenham's line algorithm see wikipedea for an explaination
    Vectori offset{end.x < start.x ? -1 : 1, end.y < start.y ? -1 : 1};
    Vectori slope{(end.x < start.x) ? (start.x - end.x) : (end.x - start.x),
                  (end.y < start.y) ? (start.y - end.y) : (end.y - start.y)};
    int error = slope.x - slope.y;

    Vectoru pos = start;

    operator[](pos) = value;
    while (pos != end) {
        int e2 = 2 * error;
        if (e2 > -slope.y) {
            error -= slope.y;
            pos.x += offset.x;
        }
        if (e2 < slope.x) {
            error += slope.x;
            pos.y += offset.y;
        }
        operator[](pos) = value;
    }
}

template <typename T>
void Grid<T>::fillBox(const Vectoru& start, const Vectoru& end, T value)
{
    Vectoru topLeft{std::min(start.x, end.x), std::min(start.y, end.y)};
    Vectoru bottomRight{std::max(start.x, end.x), std::max(start.y, end.y)};

    for (unsigned i = topLeft.x; i <= bottomRight.x; ++i) {
        for (unsigned j = topLeft.y; j <= bottomRight.y; ++j) {
            operator[](Vectoru{i, j}) = value;
        }
    }
}

template <typename T>
void Grid<T>::outlineBox(const Vectoru& start, const Vectoru& end, T value)
{
    Vectoru topLeft{std::min(start.x, end.x), std::min(start.y, end.y)};
    Vectoru bottomRight{std::max(start.x, end.x), std::max(start.y, end.y)};

    for (unsigned i = topLeft.x; i <= bottomRight.x; ++i) {
        operator[](Vectoru{i, topLeft.y}) = value;
        operator[](Vectoru{i, bottomRight.y}) = value;
    }
    for (unsigned j = topLeft.y; j <= bottomRight.y; ++j) {
        operator[](Vectoru{topLeft.x, j}) = value;
        operator[](Vectoru{bottomRight.x, j}) = value;
    }
}

} // namespace tank

#endif // TANK_GRID_HPP
