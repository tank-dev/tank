#ifndef TANK_EVENTS_HPP
#define TANK_EVENTS_HPP

#include <SFML/Window/Event.hpp>
#include <set>
#include <functional>

namespace tank {

class EventHandler
{
public:
    class Connection;
    using Condition = std::function<bool()>;
    using Effect = std::function<void()>;

private:
    class ConnectedPair {
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

        bool operator<(const ConnectedPair& rhs) const {
            return this->uid < rhs.uid;
        }
    };

    using ConnectedPairList = std::set<ConnectedPair>;
    ConnectedPairList connections;

    void disconnect(Connection& connection);

public:
    Connection connect(Condition condition, Effect effect);

    void propagate();
};

class EventHandler::Connection
{
    EventHandler& events;
    ConnectedPairList::iterator iterator;
    bool connected = true;

public:
    Connection(EventHandler& events, ConnectedPairList::iterator iterator) :
        events{events},
        iterator{iterator}
    {
    }

    ~Connection() {
        disconnect();
    }

    void disconnect() {
        if (not connected) {return;}
        connected = false;
        events.disconnect(*this);
    }

    ConnectedPairList::iterator getIterator() {return iterator;}

    bool isConnected() const {
        return connected;
    }
};

}

#endif //TANK_EVENTS_HPP
