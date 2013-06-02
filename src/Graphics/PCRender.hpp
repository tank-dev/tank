#pragma once
#ifndef PCRENDER_H
#define	PCRENDER_H

#include "IRender.hpp"

#include <map>
#include <string>

struct SDL_Surface;

class PCRender : public IRender
{
public:
    /* IRender method overrides */
    //Initialization
    virtual bool initialize();

    //Rendering
    virtual void draw(Texture const* texture,
                      Vector  const& position);
    virtual void draw(Texture const* texture,
                      Vector  const& position,
                      Rect    const& clip);

    virtual void drawText(char const* text, Vector const& position);
    virtual void flipDisplay();

    //Image loading/retrieval
    virtual Texture const* getTexture(char const* name);
    virtual bool           loadImage(char const* name, char const* fileName);

    /* Constructor and Destructor */
    PCRender();
    virtual ~PCRender();
private:
    std::map<std::string, Texture> _textures;

    /* Implementation-specific private data */
    SDL_Surface* _screen;
    std::map<std::string, SDL_Surface*> _images;
};
#endif
