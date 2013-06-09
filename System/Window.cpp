#include "Window.hpp"

#include <iostream>

bool Window::windowExists_ = false;

Window::Window(int width, int height, int flags)
    :caption_(""),
    size_({width, height}),
    valid_(false)
{
    if(!windowExists_)
    {
        valid_ = true;
        bool success = true;

        std::cout << "Opening Window" << std::endl;

        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            std::cout << "OH GOD, SDL REALLY COCKED UP PROPER: ";
            std::cout << SDL_GetError() << std::endl;
            success = false;
        }

        if(IMG_Init(IMG_INIT_PNG) == -1)
        {
            std::cout << "Something went wrong: " << IMG_GetError() << std::endl;
            success = false;
        }

        if(SDL_SetVideoMode(width, height, 32, flags) == NULL)
        {
            std::cout << "OH NOEZ: " << SDL_GetError() << std::endl;
            success = false;
        }

        windowExists_ = success;
    }
}

Window::~Window()
{
    if(windowExists_ && valid_)
    {
        std::cout << "Closing Window" << std::endl;

        IMG_Quit();
        SDL_Quit();
    }
}

void Window::setWidth(int width, int height)
{
    //Unfortunately SDL will create a new window, which is generally
    //undesired, so this function shouldn't do anything
}

void Window::setIcon(std::string&& path)
{
    if(windowExists_ && valid_)
    {
        SDL_WM_SetIcon(IMG_Load(path.c_str()), NULL);
    }
}

void Window::setCaption(std::string&& caption)
{
    if(windowExists_ && valid_)
    {
        SDL_WM_SetCaption(caption.c_str(), NULL);
    }
}

Vectori const& Window::getSize()
{
    return size_;
}

std::string const& Window::getCaption()
{
    return caption_;
}
