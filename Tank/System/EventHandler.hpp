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

#ifndef TANK_EVENTS_HPP
#define TANK_EVENTS_HPP

#include <memory>
#include <set>
#include <functional>
#include <SFML/Window/Event.hpp>

namespace tank {

class EventHandler
{
public:
    class Connection;

    using Condition = std::function<bool()>;
    using Effect = std::function<void()>;

private:
    class ConnectedPair
    {
        static std::size_t counter;
        std::size_t uid;

    public:
        Condition condition;
        Effect effect;


        ConnectedPair(Condition condition, Effect effect) :
            uid{counter},
            condition{condition},
            effect{effect}
        {
            ++counter;
        }

        // std::set boilerplate
        bool operator<(const ConnectedPair& rhs) const
        {
            return this->uid < rhs.uid;
        }
    };

    using ConnectedPairList = std::set<ConnectedPair>;
    ConnectedPairList connections;

    void disconnect(Connection& connection);
public:
    std::unique_ptr<Connection> connect(Condition condition, Effect effect);

    void propagate();
};

class EventHandler::Connection
{
    EventHandler& events;
    ConnectedPairList::iterator iterator;
    bool connected = true;

public:
    Connection(EventHandler& events, ConnectedPairList::iterator iterator) :
        events(events),
        iterator(iterator)
    {
    }

    ~Connection()
    {
        disconnect();
    }

    void disconnect()
    {
        if (not connected) {return;} // Jamie: Will this ever happen?
        connected = false;
        events.disconnect(*this);
    }

    ConnectedPairList::iterator getIterator() {return iterator;}

    bool isConnected() const {
        return connected;
    }
};

}

inline std::function<bool()> operator&& (std::function<bool()> f1,
                                         std::function<bool()> f2)
{
    return [f1,f2]()
    {
        return f1() and f2();
    };
}

inline std::function<bool()> operator|| (std::function<bool()> f1,
                                         std::function<bool()> f2)
{
    return [f1,f2]()
    {
        return f1() or f2();
    };
}
#endif //TANK_EVENTS_HPP
