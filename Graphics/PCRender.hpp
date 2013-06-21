#pragma once
#ifndef TANK_PCRENDER_HPP
#define	TANK_PCRENDER_HPP

#include "IRender.hpp"

#include <map>
#include <string>

struct SDL_Surface;

namespace tank {

class PCRender : public IRender
{
public:
    /* IRender method overrides */
    //Initialization
    virtual bool initialize();

    //Rendering
    virtual void draw(Texture const* texture,
                      Vectorf  const& position);
    virtual void draw(Texture const* texture,
                      Vectorf  const& position,
                      Rect    const& clip);

    virtual void drawText(char const* text, Vectorf const& position);
    virtual void flipDisplay();

    //Image loading/retrieval
    virtual Texture const* getTexture(char const* name);
    virtual bool           loadImage(char const* name, char const* fileName);

    /* Constructor and Destructor */
    PCRender();
    virtual ~PCRender();
private:
    std::map<std::string, Texture> textures_;

    /* Implementation-specific private data */
    SDL_Surface* screen_;
    std::map<std::string, SDL_Surface*> images_;
};

}

#endif
