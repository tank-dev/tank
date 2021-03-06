// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_WINDOW_HPP
#define TANK_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "../Graphics/Color.hpp"
#include "../Utility/Vector.hpp"

namespace sf {
class Event;
}

namespace tank {

class Window
{
    sf::RenderWindow window_;
    std::string caption_;
    Vector<unsigned int> size_;

    // Is this window instance the current window?
    bool valid_;

    Color backgroundColor_;

    // Unfortunately we can only have one window right now
    static bool windowExists_;

public:
    Window(Vector<unsigned int> size, std::string caption = "");
    Window(Window const&) = delete;
    Window& operator=(Window const&) = delete;
    virtual ~Window();

    virtual Vector<unsigned int> getSize();
    virtual std::string getCaption();

    virtual void flipDisplay();

    virtual sf::RenderWindow& SFMLWindow()
    {
        return window_;
    }

    virtual void setSize(Vectoru size);
    virtual void setCaption(std::string caption);

    virtual void setBackgroundColor(Color c) { backgroundColor_ = c; }
    virtual void setBackgroundColor(float r, float g, float b, float a = 1.f);

    /*!
     * \brief SFML-specific polling code (temporary)
     */
    bool pollEvent(sf::Event&);

    /*!
     * \brief Not implemented
     */
    virtual void setIcon(std::string path);
};
}

#endif /* WINDOW_H */
