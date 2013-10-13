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

#ifndef TANK_KEYBOARD_HPP
#define TANK_KEYBOARD_HPP
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <array>

namespace tank {

using Key = sf::Keyboard::Key;

class Keyboard
{
    friend class Game;
    static std::array<bool, Key::KeyCount> currentState_;
    static std::array<bool, Key::KeyCount> lastState_;

public:
    static std::function<bool()> KeyDown(Key key) {
        return [key]() {
            return isKeyDown(key);
        };
    }

    static std::function<bool()> KeyUp(Key key) {
        return [key]() {
            return not isKeyDown(key);
        };
    }

    static std::function<bool()> KeyPressed(Key key) {
        return [key]() {
            return isKeyPressed(key);
        };
    }

    static std::function<bool()> KeyReleased(Key key) {
        return [key]() {
            return not isKeyReleased(key);
        };
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
        return currentState_[key] and not lastState_[key];
    }

    static bool isKeyReleased(Key key)
    {
        return not currentState_[key] and lastState_[key];
    }

private:
    static void update();
};

}

#endif /* TANK_KEYBOARD_HPP */
