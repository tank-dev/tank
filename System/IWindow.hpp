#pragma once
#ifndef IWINDOW_H
#define IWINDOW_H

#include <string>
#include "../Utility/Vector.hpp"

namespace sf
{
    class Event;
}

class IWindow
{
public:
    IWindow() {}
    virtual ~IWindow() {}

    virtual Vector<unsigned int> const& getSize() = 0;
    virtual std::string const& getCaption() = 0;

    virtual void render();
    virtual void flipBuffer();

    /*!
     * \brief SFML-specific polling code (temporary)
     */
    virtual bool pollEvent(sf::Event&);

    virtual void resize(Vector<unsigned int> const& size) = 0;
    virtual void setCaption(std::string& caption) = 0;
    virtual void setIcon(std::string& path) = 0;
private:
    IWindow(IWindow const&);
    IWindow& operator=(IWindow const&);
};

#endif /* IWINDOW_H */
