#ifndef TANK_EVENTS_HPP
#define TANK_EVENTS_HPP

#include <SFML/Window/Event.hpp>
//#include <boost/signals2/signal.hpp>
//#include <vector>
#include <set>
#include <functional>
#include <boost/container/stable_vector.hpp>

namespace tank {

class EventHandler
{
    using Condition = std::function<bool()>;
    using Effect = std::function<void()>;

    class ConnectedPair {
    private:
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

public:
    class Connection;

    Connection connect(Condition condition, Effect effect);
    void disconnect(Connection& connection);
//    Connection connect(std::initializer_list<Condition> conditions, Effect effect);

    void propagate();
};

class EventHandler::Connection
{
    EventHandler& events;
    ConnectedPairList::iterator iterator;
    bool valid = true;

public:
    Connection(EventHandler& events, ConnectedPairList::iterator iterator) :
        events{events},
        iterator{iterator}
    {
    }

    ~Connection() {
        if (valid) {
            events.disconnect(*this);
        }
    }

    void setInvalid() {valid = false;}
    ConnectedPairList::iterator getIterator() {return iterator;}
};

}

#endif //TANK_EVENTS_HPP
