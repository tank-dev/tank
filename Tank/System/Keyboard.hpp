#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <SFML/Window/Keyboard.hpp>
#include <functional>

namespace tank {

using Key = sf::Keyboard::Key;

class Keyboard
{
public:
    static std::function<bool()> KeyPressed(Key key) {
        return [key]() {
            return sf::Keyboard::isKeyPressed(key);
        };
    }
};

}

#endif // KEYBOARD_HPP
