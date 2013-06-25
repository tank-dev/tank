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

#ifndef TANK_IWINDOW_HPP
#define TANK_IWINDOW_HPP

#include <string>
#include "../Utility/Vector.hpp"
namespace sf
{
    class Event;
    class RenderWindow;
}

namespace tank {

/*!
 * \brief Base virtual class (interface) for windows
 */
class IWindow
{
public:
    IWindow() = default;
    virtual ~IWindow() = default;

    virtual Vector<unsigned int> const& getSize() = 0;
    virtual std::string getCaption() = 0;

    virtual void flipDisplay() = 0;

    virtual sf::RenderWindow& SFMLWindow() = 0;

    /*!
     * \brief SFML-specific polling code (temporary)
     */
    virtual bool pollEvent(sf::Event&) = 0;

    virtual void setBackgroundColor(float r, float g, float b, float a = 1.f) = 0;
    virtual void resize(Vector<unsigned int> const& size) = 0;
    virtual void setCaption(std::string caption) = 0;
    virtual void setIcon(std::string path) = 0;
private:
    IWindow(IWindow const&);
    IWindow& operator=(IWindow const&);
};

}

#endif /* IWINDOW_H */
