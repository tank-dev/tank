#ifndef WINDOW_H
#define	WINDOW_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "IWindow.hpp"
#include "../Utility/Vector.hpp"

class Window : public IWindow
{
public:
    Window(int width, int height, int flags = SDL_HWSURFACE);
    virtual ~Window();

    virtual Vectori const& getSize();
    virtual std::string const& getCaption();

    virtual void setWidth(int width, int height);   //Doesn't work
    virtual void setCaption(std::string&& caption);
    virtual void setIcon(std::string&& path);
private:
    std::string caption_;
    Vectori size_;

    //Is this window instance the current window?
    bool valid_;

    //Unfortunately we can only have one window to stop SDL from shitting itself
    static bool windowExists_;

    //Make SDL happen
    static void initialize();
};

#endif /* WINDOW_H */
