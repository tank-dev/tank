#include "Window.hpp"

#include <iostream>

Window::Window() {}
Window::~Window()
{
    std::cout << "Closing Window" << std::endl;
    
    IMG_Quit();
    SDL_Quit();
}

bool Window::Initialize()
{
    std::cout << "Opening Window" << std::endl;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "OH NOEZ, SDL REALLY COCKED UP PROPER: " << SDL_GetError() << std::endl;
        return false;
    }
    
    if(IMG_Init(IMG_INIT_PNG) == -1)
    {
        std::cout << "Something went wrong: " << IMG_GetError() << std::endl;
        return false;
    }
    
    SDL_WM_SetIcon(IMG_Load("res/Ico.png"), NULL );
    SDL_WM_SetCaption( "Chelonian Island", NULL );
    
    if(SDL_SetVideoMode(640, 640, 32, SDL_HWSURFACE) == NULL)
    {
        std::cout << "OH NOEZ: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

Window *Window::_instance = NULL;

Window *Window::Instance()
{
    if (_instance == NULL)
    {
        _instance = new Window;
    }
    return _instance;
}
