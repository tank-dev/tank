#pragma once
#ifndef IRENDER_H
#define IRENDER_H

#include <string>

#include "../Utility/Rect.hpp"
#include "../Utility/Vector.hpp"
#include "../Graphics/Texture.hpp"

class IRender
{
public:
    virtual bool initialize() = 0;

    virtual void draw(Texture const* texture,
                      Vector  const& position) = 0;
    virtual void draw(Texture const* texture,
                      Vector  const& position,
                      Rect    const& clip)     = 0;

    virtual void drawText(char const* text, Vector const& position) = 0;

    virtual void flipDisplay() = 0;

    virtual Texture const* getTexture(char const* name) = 0;
    virtual bool loadImage(char const* name, char const* fileName) = 0;

    virtual ~IRender() {}
};

class NullRender : public IRender
{
public:
    virtual bool initialize() {
        return true;
    }

    virtual void draw(Texture const* texture,
                      Vector  const& position) {}
    virtual void draw(Texture const* texture,
                      Vector  const& position,
                      Rect    const& clip)     {}

    virtual void drawText(char const* text, Vector const& position) {}

    virtual void flipDisplay() {}

    virtual Texture const* getTexture(char const* name) {
        return NULL;
    }
    virtual bool           loadImage(char const* name, char const* fileName) {
        return true;
    }
};
#endif
