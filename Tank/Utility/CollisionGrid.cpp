// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "CollisionGrid.hpp"

namespace tank
{

// Retraces the path until we reach the start then reverse it
inline std::vector<Vectoru> retracePath(const std::unordered_map<Vectoru, std::pair<Vectoru, float>>& cameFrom, Vectoru currentNode)
{
    std::vector<Vectoru> path{currentNode};

    auto nextNode = cameFrom.find(currentNode);
    while (nextNode->second.first != nextNode->first)
    {
        currentNode = nextNode->second.first;
        path.push_back(currentNode);
        nextNode = cameFrom.find(currentNode);
    }

    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<Vectoru> CollisionGrid::getPath(const Vectoru& start, const Vectoru& end) const
{
    // This use's the A* algorithm to find a path between to points on the grid.

    if (start == end)
    {
        // We are looking for a path to the same place we don't need no algorithm
        return std::vector<Vectoru>{start};
    }
    std::unordered_set<Vectoru> closed;
    // A multimap of nodes with key the huristic score for the node.
    std::multimap<float, Vectoru> open;
    open.insert(std::make_pair(pathHeuristic(start, end), start));

    // A map of points to (where they came from, the cost using that connection)
    std::unordered_map<Vectoru, std::pair<Vectoru, float>> cameFrom;
    cameFrom.insert(std::make_pair(start, std::make_pair(start, 0)));

    auto currentNode = open.upper_bound(-1.0f);
    // Look until we've ran out of places to look
    while (currentNode != open.end())
    {
        // If we've already dealt with this node ignore it.
        // Having this here is to aviod having to search and remove old values
        // for an open point if we find new ones.
        if (closed.find(currentNode->second) == closed.end())
        {
            Vectoru point = currentNode->second;
            if (point == end)
            {
                // We have found a path so return it.
                return retracePath(cameFrom, end);
            }
            float costSoFar = cameFrom.find(point)->second.second;

            if (point.y != 0)
            {
                checkDirection(closed, open, cameFrom, end, point, Vectoru{0,-1}, costSoFar);
            }
            if (point.y + 1 != getHeight())
            {
                checkDirection(closed, open, cameFrom, end, point, Vectoru{0,1}, costSoFar);
            }
            if (point.x != 0)
            {
                checkDirection(closed, open, cameFrom, end, point, Vectoru{-1,0}, costSoFar);
                if (point.y != 0)
                {
                    checkDirection(closed, open, cameFrom, end, point, Vectoru{-1,-1}, costSoFar);
                }
                if (point.y + 1 != getHeight())
                {
                    checkDirection(closed, open, cameFrom, end, point, Vectoru{-1,1}, costSoFar);
                }
            }
            if (point.x + 1 != getWidth())
            {
                checkDirection(closed, open, cameFrom, end, point, Vectoru{1,0}, costSoFar);
                if (point.y != 0)
                {
                    checkDirection(closed, open, cameFrom, end, point, Vectoru{1,-1}, costSoFar);
                }
                if (point.y + 1 != getHeight())
                {
                    checkDirection(closed, open, cameFrom, end, point, Vectoru{1,1}, costSoFar);
                }
            }

            // Add the point to the set of closed vetrices
            closed.insert(currentNode->second);
        }
        // Remove the point from the set of open vetrices
        open.erase(currentNode);
        // Go to the next node
        currentNode = open.upper_bound(-1.0f);
    }

    // We have failed in finding a path return the empty path
    return std::vector<Vectoru>{};
}

float CollisionGrid::pathHeuristic(const Vectorf& start, const Vectorf& end) const
{
    return (start - end).magnitude();
}

float CollisionGrid::getCost(const Vectorf& start, const Vectorf& end) const
{
    return (start - end).magnitude();
}

} // namespace tank
