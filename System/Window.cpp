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

#include "Window.hpp"

#include <iostream>
#include "Game.hpp"

namespace tank {

bool Window::windowExists_ = false;

Window::Window(Vector<unsigned int> const& size, std::string caption)
    : caption_(caption)
    , size_(size)
    , valid_(false)
{
    if(!windowExists_)
    {
        valid_ = true;

        Game::log << "Opening Window" << std::endl;

        sf::ContextSettings settings;
        settings.antialiasingLevel = 4;
        settings.majorVersion = 3;
        settings.minorVersion = 2;
        sf::VideoMode vMode = sf::VideoMode::getDesktopMode();
        vMode.width = size.x;
        vMode.height = size.y;
        window_.create(vMode, caption,
                      sf::Style::Default, settings);

        window_.setFramerateLimit(60);
        setBackgroundColor(0.f,0.f,0.f);

        valid_ = true;
        windowExists_ = true;
    }
    else
    {
        Game::log << "Window already exists" << std::endl;
    }
}

Window::~Window()
{
    if (windowExists_ && valid_)
    {
        Game::log << "Closing Window" << std::endl;
        windowExists_ = false;
    }
}

bool Window::pollEvent(sf::Event& event)
{
    return window_.pollEvent(event);
}

void Window::flipDisplay()
{
    window_.display();
    window_.clear(backgroundColor_);
}

void Window::resize(Vector<unsigned int> const& size)
{
    window_.setSize({size.x, size.y});
}

void Window::setBackgroundColor(float r, float g, float b, float a)
{
    backgroundColor_.r = 255 * r;
    backgroundColor_.g = 255 * g;
    backgroundColor_.b = 255 * b;
    backgroundColor_.a = 255 * a;
}

void Window::setIcon(std::string path)
{
    if(windowExists_ && valid_)
    {
        //SDL_WM_SetIcon(IMG_Load(path.c_str()), NULL);
    }
}

void Window::setCaption(std::string caption)
{
    if(windowExists_ && valid_)
    {
        caption_ = caption;
        //SDL_WM_SetCaption(caption.c_str(), NULL);
    }
}

Vector<unsigned int> const& Window::getSize()
{
    return size_;
}

std::string Window::getCaption()
{
    return caption_;
}

}
