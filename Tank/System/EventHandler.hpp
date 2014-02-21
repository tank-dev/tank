// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

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

inline std::function<bool()> fnot (std::function<bool()> f)
{
	return [f]()
	{
		return not f();
	};
}

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

/*inline std::function<bool()> operator! (std::function<bool()> f)
{
    return [f]()
    {
        return not f();
    };
}*/

#endif //TANK_EVENTS_HPP
