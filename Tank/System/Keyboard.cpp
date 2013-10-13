#include "Keyboard.hpp"

#include <algorithm>
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
