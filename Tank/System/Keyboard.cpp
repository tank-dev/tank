#include "Keyboard.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <SFML/Window/Keyboard.hpp>

namespace tank {

std::array<bool, Key::KeyCount> Keyboard::currentState_ {};
std::array<bool, Key::KeyCount> Keyboard::lastState_ {};

void Keyboard::update()
{
    std::copy(currentState_.begin(), currentState_.end(), lastState_.begin());
    for (int i = 0; i < Key::KeyCount; ++i)
    {
        currentState_[i] = sf::Keyboard::isKeyPressed(static_cast<Key>(i));
    }
}

} /* namespace tank */
