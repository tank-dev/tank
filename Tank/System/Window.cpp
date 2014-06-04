// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Window.hpp"

#include <iostream>
#include "Game.hpp"

namespace tank
{

bool Window::windowExists_ = false;

Window::Window(Vector<unsigned int> const& size, std::string caption)
        : caption_(caption), size_(size), valid_(false)
{
    if (!windowExists_) {
        valid_ = true;

        Game::log << "Opening Window" << std::endl;

        sf::ContextSettings settings;
        settings.antialiasingLevel = 4;
        sf::VideoMode vMode = sf::VideoMode::getDesktopMode();
        vMode.width = size.x;
        vMode.height = size.y;
        window_.create(vMode, caption, sf::Style::Close | sf::Style::Titlebar,
                       settings);

        window_.setFramerateLimit(60);
        window_.setVerticalSyncEnabled(true);
        setBackgroundColor(0.f, 0.f, 0.f);

        valid_ = true;
        windowExists_ = true;
    } else {
        Game::log << "Window already exists" << std::endl;
    }
}

Window::~Window()
{
    if (windowExists_ && valid_) {
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
    if (windowExists_ && valid_) {
        // SDL_WM_SetIcon(IMG_Load(path.c_str()), nullptr);
    }
}

void Window::setCaption(std::string caption)
{
    if (windowExists_ && valid_) {
        caption_ = caption;
        window_.setTitle(caption);
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
