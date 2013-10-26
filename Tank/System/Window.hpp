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

#ifndef TANK_WINDOW_HPP
#define TANK_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include "../Utility/Vector.hpp"

namespace sf
{
    class Event;
}

namespace tank {

class Window
{
public:
    Window(Vector<unsigned int> const& size, std::string caption = "");
    virtual ~Window();

    virtual Vector<unsigned int> const& getSize();
    virtual std::string getCaption();

    virtual void flipDisplay();

    virtual sf::RenderWindow& SFMLWindow() { return window_; }

    virtual void resize(Vector<unsigned int> const& size);
    virtual void setCaption(std::string caption);

    virtual void setBackgroundColor(float r, float g, float b,
                                    float a = 1.f);

    /*!
     * \brief SFML-specific polling code (temporary)
     */
    bool pollEvent(sf::Event&);

    /*!
     * \brief Not implemented
     */
    virtual void setIcon(std::string path);
private:
    sf::RenderWindow window_;
    std::string caption_;
    Vector<unsigned int> size_;

    //Is this window instance the current window?
    bool valid_;

    sf::Color backgroundColor_;

    //Unfortunately we can only have one window right now
    static bool windowExists_;
};

}

#endif /* WINDOW_H */
