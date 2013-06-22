#include "Window.hpp"

#include <iostream>
#include <GL/glew.h> 
#include <SFML/OpenGL.hpp>
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
        Game::log << "Opening Window" << std::endl;

        sf::ContextSettings settings;
        settings.antialiasingLevel = 4;
        settings.majorVersion = 3;
        settings.minorVersion = 3;
        sf::VideoMode vMode = sf::VideoMode::getDesktopMode();
        vMode.width = size.x;
        vMode.height = size.y;
        window_.create(vMode, caption,
                      sf::Style::Default, settings);

        window_.setFramerateLimit(60);
        glClearColor(1.f,0.f,1.f,1.f);
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
    if(windowExists_ && valid_)
    {
        Game::log << "Closing Window" << std::endl;
        windowExists_ = false;
    }
}

bool Window::pollEvent(sf::Event& event)
{
    return window_.pollEvent(event);
}

void Window::render()
{
}

void Window::flipDisplay()
{
    window_.display();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::resize(Vector<unsigned int> const& size)
{
    window_.setSize({size.x, size.y});
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
