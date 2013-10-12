#include "EventHandler.hpp"
#include <numeric>

namespace tank {
std::size_t EventHandler::ConnectedPair::counter = 0;

void EventHandler::propagate()
{
    for (auto& x : connections) {
        if (x.condition()) {
            x.effect();
        }
    }
}

std::unique_ptr<EventHandler::Connection> EventHandler::connect(Condition condition,
                                               Effect effect)
{
    auto iter = this->connections.emplace(condition,effect);
    return std::unique_ptr<EventHandler::Connection>(new EventHandler::Connection{*this, iter.first});
}

void EventHandler::disconnect(Connection& connection)
{
    connections.erase(connection.getIterator());
}

}
