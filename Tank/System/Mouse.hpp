#ifndef TANK_MOUSE_HPP
#define TANK_MOUSE_HPP
#include <functional>
#include <SFML/Window/Mouse.hpp>
#include "../../Tank/Utility/Vector.hpp"

namespace tank {

class Mouse {
public:
    using Button = sf::Mouse::Button;
    static tank::Vectori getPosition();

    static bool isButtonPressed(Button button);
    static std::function<bool()> ButtonPressed(Button button);
};
}

#endif //TANK_MOUSE_HPP
