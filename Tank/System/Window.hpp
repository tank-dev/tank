// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_WINDOW_HPP
#define TANK_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include "../Utility/Vector.hpp"

namespace sf
{
class Event;
}

namespace tank
{

class Window
{
public:
    Window(Vector<unsigned int> const& size, std::string caption = "");
    virtual ~Window();

    virtual Vector<unsigned int> const& getSize();
    virtual std::string getCaption();

    virtual void flipDisplay();

    virtual sf::RenderWindow& SFMLWindow()
    {
        return window_;
    }

    virtual void resize(Vector<unsigned int> const& size);
    virtual void setCaption(std::string caption);

    virtual void setBackgroundColor(float r, float g, float b, float a = 1.f);

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

    // Is this window instance the current window?
    bool valid_;

    sf::Color backgroundColor_;

    // Unfortunately we can only have one window right now
    static bool windowExists_;
};
}

#endif /* WINDOW_H */
