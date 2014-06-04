// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_KEYBOARD_HPP
#define TANK_KEYBOARD_HPP
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <array>

namespace tank
{

using Key = sf::Keyboard::Key;

class Keyboard
{
    friend class Game;
    static bool stateChange_;
    static std::array<bool, Key::KeyCount> currentState_;
    static std::array<bool, Key::KeyCount> lastState_;

public:
    static std::function<bool()> KeyDown(Key key)
    {
        return [key]() { return isKeyDown(key); };
    }

    static std::function<bool()> KeyUp(Key key)
    {
        return [key]() { return not isKeyDown(key); };
    }

    static std::function<bool()> KeyPress(Key key)
    {
        return [key]() { return isKeyPressed(key); };
    }

    static std::function<bool()> KeyRelease(Key key)
    {
        return [key]() { return isKeyReleased(key); };
    }

    static bool isKeyDown(Key key)
    {
        return currentState_[key];
    }

    static bool isKeyUp(Key key)
    {
        return not isKeyDown(key);
    }

    static bool isKeyPressed(Key key)
    {
        return stateChange_ and currentState_[key] and not lastState_[key];
    }

    static bool isKeyReleased(Key key)
    {
        return stateChange_ and not currentState_[key] and lastState_[key];
    }

private:
    static void reset();

    static void setKeyPressed(Key key);
    static void setKeyReleased(Key key);
};
}

#endif /* TANK_KEYBOARD_HPP */
