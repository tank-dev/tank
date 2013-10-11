#include <Tank/System/EventHandler.hpp>
#include <Tank/Utility/Timer.hpp>
#include <iostream>
#include <thread>
#include <functional>

inline constexpr std::chrono::duration<int64_t, std::milli> operator"" _ms (unsigned long long i) {
    return std::chrono::milliseconds(i);
}


std::function<bool()> operator||(std::function<bool()> f1, std::function<bool()> f2) {
    return [f1, f2]() {
        return f1() || f2();
    };
}

std::function<bool()> operator&&(std::function<bool()> f1, std::function<bool()> f2) {
    return [f1, f2]() {
        return f1() && f2();
    };
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

void hello()
{
    std::cout << "Hello World!" << std::endl;
}



int main()
{
    tank::Timer timer;
    tank::EventHandler events;

    tank::EventHandler::Connection c = events.connect(is_3_seconds(timer), hello);
    timer.start();


    while(timer.getTicks() < 5000) {
        events.propagate();
        if (timer.getTicks() > 3002) {
            c.disconnect();
        }
        std::this_thread::sleep_for(1_ms);
    }

}
