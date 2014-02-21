// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

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
