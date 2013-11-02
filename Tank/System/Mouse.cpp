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
