#ifndef WINDOW_H
#define	WINDOW_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Window
{
public:
    bool Initialize();

    static Window* Instance();
    ~Window();
private:
    static Window* _instance;
    Window();
};
#endif
