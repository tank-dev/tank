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

#include "Keyboard.hpp"

#include <algorithm>
#include <array>
#include <iterator>
#include <SFML/Window/Keyboard.hpp>

namespace tank {

bool Keyboard::stateChange_ {false};
std::array<bool, Key::KeyCount> Keyboard::currentState_ {};
std::array<bool, Key::KeyCount> Keyboard::lastState_ {};

void Keyboard::reset()
{
    if (stateChange_)
    {
        std::copy(currentState_.begin(), currentState_.end(), lastState_.begin());
    }

    stateChange_ = false;
}

void Keyboard::setKeyPressed(Key key)
{
    stateChange_ = true;
    currentState_[key] = true;
}

void Keyboard::setKeyReleased(Key key)
{
    stateChange_ = true;
    currentState_[key] = false;
}

} /* namespace tank */
