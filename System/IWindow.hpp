#pragma once
#ifndef IWINDOW_H
#define IWINDOW_H

#include <string>
#include "../Utility/Vector.hpp"

class IWindow
{
public:
    IWindow();
    virtual ~IWindow();

    virtual Vector const& getSize() = 0;
    virtual std::string const& getCaption() = 0;

    virtual void setWidth(int width, int height) = 0;
    virtual void setCaption(std::string&& caption) = 0;
    virtual void setIcon(std::string&& path) = 0;
private:
    IWindow(IWindow const&);
    IWindow& operator=(IWindow const&);
};

#endif /* IWINDOW_H */
