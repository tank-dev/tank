// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "EventHandler.hpp"
#include <numeric>

namespace tank
{
std::size_t EventHandler::ConnectedPair::counter = 0;

void EventHandler::propagate()
{
    for (auto& x : connections) {
        if (x.condition()) {
            x.effect();
        }
    }
}

std::unique_ptr<EventHandler::Connection>
        EventHandler::connect(Condition condition, Effect effect)
{
    auto iter = this->connections.emplace(condition, effect);
    return std::unique_ptr<Connection>(new Connection{*this, iter.first});
}

void EventHandler::disconnect(Connection& connection)
{
    connections.erase(connection.getIterator());
}
}
