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
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#include "Texture.hpp"

#include <sstream>
#include <stdexcept>
#include <SFML/OpenGL.hpp>
#include <FreeImagePlus.h>

namespace tank {
namespace gl {
/* TODO:
 *   * Allow mipmaps
 *   * Allow different data formats
 *   * Allow multisampling
 */

unsigned int nextPowerOfTwo(unsigned int x);

Texture::Texture()
    : loaded_(false)
    , target_(GL_TEXTURE_2D)
    , scale_(glm::vec2{0.f, 0.f})
    , size_({})
{
    //Register a 2D texture id
    glGenTextures(1, &name_);
}

Texture::Texture(std::string file)
    : Texture()
{
    load(file);
}

Texture::~Texture()
{
    glDeleteTextures(1, &name_);
}

void Texture::load(std::string file)
{
    if(not loaded_)
    {
        // TODO: Exception this up
        fipImage image;
        if(not image.load(file.c_str()))
        {
            std::string err = "Loading image " + file + " failed";
            throw std::runtime_error(err);
        }

        size_.x = image.getWidth();
        size_.y = image.getHeight();

        // OpenGL expects dimensions in powers of 2
        const unsigned int p2w = nextPowerOfTwo(size_.x);
        const unsigned int p2h = nextPowerOfTwo(size_.y);

        fipImage resized(FIT_BITMAP, p2w, p2h, 32);
        if(not resized.pasteSubImage(image, 0, 0))
        {
            std::string err = "Failed to resize " + file;
            throw std::runtime_error(err);
        }

        // GL will render upside down, causing problems with texture coordinate
        // operations, so flip it before loading.
        resized.flipVertical();

        const uint8_t* pixels = resized.accessPixels();

        // Need to store the ratio between resized texture and original
        scale_ = glm::vec2{static_cast<float>(p2w) / static_cast<float>(size_.x),
                           static_cast<float>(p2h) / static_cast<float>(size_.y)};

        glBindTexture(target_, name_);

        glTexImage2D(target_, 0,
                     GL_RGBA8,
                     p2w, p2h,
                     0, GL_BGRA,
                     GL_UNSIGNED_BYTE,
                     pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);

        loaded_ = true;
    }
}

void Texture::bind(Texture const* t)
{
    if(t)
    {
        glBindTexture(t->target_, t->name_);
    }
}

void Texture::unbind(Texture const* t)
{
    if(t)
    {
        glBindTexture(t->target_, 0);
    }
}

unsigned int nextPowerOfTwo(unsigned int x)
{
    unsigned int p = 1;
    while(x > p)
    {
        p <<= 1;
    }

    return p;
}

}
}
