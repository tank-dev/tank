#include <Tank/System/EventHandler.hpp>
#include <iostream>

int main()
{
    tank::EventHandler events;

    tank::EventHandler::Connection c = events.connect([&]{return true;}, []{
        std::cout << "Hello world!\n";
    });

    events.propagate();
    events.disconnect(c);
    events.propagate();
}
