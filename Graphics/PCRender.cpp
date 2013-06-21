#include "PCRender.hpp"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>
#include "Texture.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../System/Game.cpp"

namespace tank {

/* --------------------------------------- *
 * Constructor and Destructor
 * --------------------------------------- */

/////////////////////////
//// Constructor
/////////////////////////
PCRender::PCRender()
{
    screen_ = nullptr;
}

/////////////////////////
//// Destructor
/////////////////////////
PCRender::~PCRender()
{
    Game::log << "PCRender engine shutting down" << std::endl;

    for(auto iter = images_.begin(); iter != images_.end(); iter++)
    {
        SDL_FreeSurface(iter->second);
    }

    textures_.clear();
}

/* --------------------------------------- *
 * IRender method overrides
 * --------------------------------------- */

/////////////////////////
//// initialize
/////////////////////////
bool PCRender::initialize()
{
    screen_ = SDL_GetVideoSurface();
    if(screen_ == nullptr)
    {
        Game::log << "Could not retrieve video surface: " << std::string(SDL_GetError()) << std::endl;
        return false;
    }

    return true;
}

void PCRender::draw(Texture const* texture, Vectorf const& pos)
{
    //Rect r = { 0, 0, texture.w, texture.h } ;
    //draw( texture, pos, r);

    draw(texture, pos, { 0,  0,  texture->width, texture->height });
}

void PCRender::draw(Texture const* texture, Vectorf const& pos, Rect const& clip)
{
    // Retrieve SDL_Surface from Resources
    std::string tName = texture->name;

    SDL_Surface* surface = images_[tName];

    if(surface != nullptr)
    {
        // Convert position to SDL_Rect
        SDL_Rect offset;

        offset.x = pos.x;
        offset.y = pos.y;

        SDL_Rect sdlClip;

        sdlClip.x = clip.x;
        sdlClip.y = clip.y;
        sdlClip.w = clip.w;
        sdlClip.h = clip.h;

        SDL_BlitSurface(surface, &sdlClip, screen_, &offset);
    }
    else
    {
        Game::log << "Render Error: Texture does not exist (" << texture->name << ")" << std::endl;
    }
}

//TODO Make this support multiple fonts
void PCRender::drawText(char const* text, Vectorf const& pos)
{
    //TODO Get this from screen width or elsewhere
    const int maxWidth = 600;

    SDL_Surface* font = images_["fontsmall"];

    char c; // character buffer
    int length = strlen(text);
    int letterSize = font->h;
    int width = length*letterSize;
    //int height = ceil((float)width/maxWidth)*letterSize;

    if(width > maxWidth)
    {
        width = maxWidth;
    }

    /*
    SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                width,
                                                height,
                                                32,
                                                font->format->Rmask,
                                                font->format->Gmask,
                                                font->format->Bmask,
                                                font->format->Amask);
                                                */

    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.w = letterSize;
    srcRect.h = letterSize;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = pos.x;
    destRect.y = pos.y;

    for(int i = 0; i < length; ++i)
    {
        c = toupper(text[i]);

        srcRect.x = ((int)c-32)*letterSize;

        //Blit directly to the screen
        //May not work
        SDL_BlitSurface(font, &srcRect, screen_, &destRect);

        destRect.x += letterSize;

        if(destRect.x > maxWidth - letterSize)
        {
            destRect.x  = pos.x;
            destRect.y += letterSize;
        }
    }
}

void PCRender::flipDisplay()
{
    SDL_Flip(screen_);
    SDL_FillRect(screen_, nullptr, SDL_MapRGBA(screen_->format,0x66,0xFF,0xFF,0xFF));
}

bool PCRender::loadImage(char const* name, char const* fileName)
{
    SDL_Surface* temp = nullptr;
    SDL_Surface* optimized = nullptr;

    temp = IMG_Load(fileName);

    if(temp == nullptr)
    {
        Game::log << SDL_GetError() << std::endl;

        return false;
    }

    optimized = SDL_DisplayFormatAlpha(temp);

    SDL_FreeSurface(temp);

    if(optimized  == nullptr)
    {
        Game::log << SDL_GetError() << std::endl;

        return false;
    }

    images_.insert(std::pair<std::string, SDL_Surface*>(name, optimized));

    Texture t = { name, optimized->w, optimized->h };

    textures_.insert(std::pair<std::string, Texture>(name, t));

    return true;
}

Texture const* PCRender::getTexture(char const* name)
{
    std::string strName = name;

    return &textures_[strName];
}

}
