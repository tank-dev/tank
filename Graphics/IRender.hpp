#pragma once
#ifndef TANK_IRENDER_HPP
#define TANK_IRENDER_HPP

#include <string>

#include "../Utility/Rect.hpp"
#include "../Utility/Vector.hpp"
#include "../Graphics/Texture.hpp"

//TODO Implement 2D OpenGL to remove stupid dependencies
class IRender
{
public:
    virtual bool initialize() = 0;

    virtual void draw(Texture const* texture,
                      Vectorf const& position) = 0;
    virtual void draw(Texture const* texture,
                      Vectorf const& position,
                      Rect    const& clip)     = 0;

    virtual void drawText(char const* text, Vectorf const& position) = 0;

    virtual void flipDisplay() = 0;

    virtual Texture const* getTexture(char const* name) = 0;
    virtual bool loadImage(char const* name, char const* fileName) = 0;

    virtual ~IRender() {}
};

class NullRender final : public IRender
{
public:
    virtual bool initialize()
    {
        return true;
    }

    virtual void draw(Texture const* texture,
                      Vectorf const& position) override;
    virtual void draw(Texture const* texture,
                      Vectorf const& position,
                      Rect    const& clip) override;

    virtual void drawText(char const* text, Vectorf const& position) override;

    virtual void flipDisplay() override;

    virtual Texture const* getTexture(char const* name) override;
    virtual bool loadImage(char const* name, char const* fileName) override;
};
#endif
