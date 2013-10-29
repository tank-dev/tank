#include "Mouse.hpp"
#include "../System/Game.hpp"

namespace tank {
tank::Vectori Mouse::getPosition() {
    auto& window = tank::Game::window()->SFMLWindow();
    auto pos = sf::Mouse::getPosition(window);
    return {pos.x, pos.y};
}

bool Mouse::isButtonPressed(Button button) {
    return sf::Mouse::isButtonPressed(button);
}

std::function<bool()> Mouse::ButtonPressed(Button button)
{
    return [button]
    {
        return isButtonPressed(button);
    };
}

}
