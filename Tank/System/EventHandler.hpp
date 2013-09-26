#ifndef TANK_EVENTS_HPP
#define TANK_EVENTS_HPP

#include <SFML/Window/Event.hpp>
#include <boost/signals2/signal.hpp>
#include <unordered_map>
#include <functional>

namespace Tank {

class Events
{
    struct Event {
        Event(std::function<bool()> predicate) :
            predicate{predicate}, signal{} {}

        std::function<bool()> predicate;
        boost::signals2::signal<void()> signal;
    };

    std::map<std::string, std::unique_ptr<Event>> SignalMap_;

public:
    bool addEvent(std::string name, std::function<bool()> predicate);
    boost::signals2::connection registerSlot(std::string signal,
        std::function<void()> fun);
    void distribute();
};

}

#endif //TANK_EVENTS_HPP
