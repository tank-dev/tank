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

#pragma once
#ifndef TANK_IWINDOW_HPP
#define TANK_IWINDOW_HPP

#include <string>
#include "../Utility/Vector.hpp"

namespace tank {

class IWindow
{
public:
    IWindow() {}
    virtual ~IWindow() {}

    virtual Vectori const& getSize() = 0;
    virtual std::string const& getCaption() = 0;

    virtual void setWidth(int width, int height) = 0;
    virtual void setCaption(std::string&& caption) = 0;
    virtual void setIcon(std::string&& path) = 0;
private:
    IWindow(IWindow const&);
    IWindow& operator=(IWindow const&);
};

}

#endif /* IWINDOW_H */
