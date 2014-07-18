// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Keyboard.hpp"

#include <algorithm>
#include <array>
#include <iterator>
#include <SFML/Window/Keyboard.hpp>

namespace tank
{

bool Keyboard::stateChange_{false};
std::array<bool, Key::KeyCount> Keyboard::currentState_{};
std::array<bool, Key::KeyCount> Keyboard::lastState_{};
bool Keyboard::keyPressed_ {false};
bool Keyboard::keyReleased_ {false};

std::function<bool()> Keyboard::Control = control;
std::function<bool()> Keyboard::Shift = shift;
std::function<bool()> Keyboard::Alt = alt;
void Keyboard::reset()
{
    if (stateChange_) {
        std::copy(currentState_.begin(), currentState_.end(),
                  lastState_.begin());
        keyPressed_ = false;
        keyReleased_ = false;
    }

    stateChange_ = false;
}

void Keyboard::setKeyPressed(Key key)
{
    stateChange_ = true;
    keyPressed_ = true;
    currentState_[key] = true;
}

void Keyboard::setKeyReleased(Key key)
{
    stateChange_ = true;
    keyReleased_ = true;
    currentState_[key] = false;
}

} /* namespace tank */
