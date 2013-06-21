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
 * Copyright (©) Jamie Bayne, David Truby, David Watson
 */

#ifndef TANK_WINDOW_HPP
#define TANK_WINDOW_HPP

#include <SDL.h>
#include <SDL_image.h>
#include "IWindow.hpp"
#include "../Utility/Vector.hpp"

namespace tank {

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
};

}

#endif /* WINDOW_H */
