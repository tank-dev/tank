#include "Events.hpp"

namespace Tank {

bool Events::addEvent(std::string name, std::function<bool ()> predicate)
{
    return SignalMap_.emplace(name,
        std::unique_ptr<Event>(new Event(predicate))).second;
}

boost::signals2::connection Events::registerSlot(std::string signal,
    std::function<void ()> fun)
{
    return SignalMap_.at(signal)->signal.connect(fun);
}

void Events::distribute()
{
    for (auto& e : SignalMap_) {
        if (e.second->predicate()) {
            e.second->signal();
        }
    }
}

}
