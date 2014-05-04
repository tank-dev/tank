// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_COLLISIONGRID_HPP
#define TANK_COLLISIONGRID_HPP

#include "Grid.hpp"

#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>

namespace tank
{

/*!
 * /brief This stores bool grid for collisions
 */
class CollisionGrid : public Grid<bool>
{
    void checkDirection(
            const std::unordered_set<Vectoru>& closed,
            std::multimap<float, Vectoru>& open,
            std::unordered_map<Vectoru, std::pair<Vectoru, float>>& cameFrom,
            Vectoru const& end, const Vectoru& point, const Vectoru& direction,
            float costSoFar) const;

public:
    CollisionGrid(const Vectoru& dims);
    CollisionGrid(const Vectoru& dims, bool intialValue);

    template<typename T>
    CollisionGrid(const Grid<T>& g, const std::unordered_set<T>& collidable);

    template<typename T>
    void loadFromGrid(const Grid<T>& g, const std::unordered_set<T>& collidable);

    std::vector<Vectoru> getPath(const Vectoru& start, const Vectoru& end) const;

    float pathHeuristic(const Vectorf& start, const Vectorf& end) const;
    float getCost(const Vectorf& start, const Vectorf& end) const;
};

template<typename T>
CollisionGrid::CollisionGrid(const Grid<T>& g, const std::unordered_set<T>& collidable)
    : Grid(g.getDimensions())
{
    loadFromGrid(g, collidable);
}

template<typename T>
void CollisionGrid::loadFromGrid(const Grid<T>& g, const std::unordered_set<T>& collidable)
{
    if (getDimensions() != g.getDimensions())
    {
        throw std::out_of_range("The grid must be the same size as the collision grid.");
    }

    size_t size = getWidth() * getHeight();
    for (size_t i = 0; i < size; ++i)
    {
        operator[](i) = collidable.find(g[i]) == collidable.end();
    }
}

// This is run on every node to add new points to the open set.
inline void CollisionGrid::checkDirection(
        const std::unordered_set<Vectoru>& closed,
        std::multimap<float, Vectoru>& open,
        std::unordered_map<Vectoru, std::pair<Vectoru, float>>& cameFrom,
        Vectoru const& end, const Vectoru& point, const Vectoru& direction,
        float costSoFar) const
{
    Vectoru checkPoint = point + direction;
    // check that the point isn't closed and we can travel through
    if (closed.find(checkPoint) == closed.end() and operator[](checkPoint))
    {
        float newCostSoFar = costSoFar + getCost(point, checkPoint);
        // Add the point to the open points
        auto pre = cameFrom.find(checkPoint);
        if (pre == cameFrom.end())
        {
            // If we don't already have a path for the point add one
            cameFrom.insert(std::make_pair(checkPoint, std::make_pair(point, newCostSoFar)));
            open.insert(std::make_pair(newCostSoFar + pathHeuristic(checkPoint, end), checkPoint));
        }
        else if (pre->second.second >= newCostSoFar)
        {
            // If the new path is shorter than the previously found path replace it
            pre->second.first = point;
            pre->second.second = newCostSoFar;
            open.insert(std::make_pair(newCostSoFar + pathHeuristic(checkPoint, end), checkPoint));
        }
    }
};

} // namespace tank

#endif // TANK_COLLISIONGRID_HPP
