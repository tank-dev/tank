// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <Tank/System/EventHandler.hpp>
#include <Tank/Utility/Timer.hpp>
#include <iostream>
#include <thread>
#include <functional>

inline constexpr std::chrono::duration<int64_t, std::milli> operator"" _ms (unsigned long long i) {
    return std::chrono::milliseconds(i);
}

std::function<bool()> is_3_seconds(const tank::Timer& timer)
{
    return [&timer](){
        return timer.getTicks() > 3000;
    };
}

std::function<bool()> is_less_1_seconds(const tank::Timer& timer)
{
    return [&]() {
        return timer.getTicks() < 2;
    };
}

std::function<bool()> isKeyPressed(sf::Keyboard::Key k)
{
    return [&]() {
        return sf::Keyboard::isKeyPressed(k);
    };
}

struct hello
{
    void operator()() const {
        std::cout << "Hello World!" << std::endl;
    }
};

int main()
{
    tank::Timer timer;
    tank::EventHandler events;

    auto c = events.connect(is_3_seconds(timer) or is_less_1_seconds(timer), hello());
    timer.start();


    while(timer.getTicks() < 5000) {
        events.propagate();
        if (timer.getTicks() > 3002) {
            c->disconnect();
        }
        std::this_thread::sleep_for(1_ms);
    }
}
