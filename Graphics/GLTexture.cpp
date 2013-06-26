#include "GLTexture.hpp"

#include <sstream>
#include <SFML/OpenGL.hpp>
#include <FreeImagePlus.h>
#include "../System/Game.hpp"

namespace tank {
/* TODO:
 *   * Allow mipmaps
 *   * Allow different data formats
 *   * Allow multisampling
 */

unsigned int nextPowerOfTwo(unsigned int x);

GLTexture::GLTexture()
    : loaded_(false)
    , target_(GL_TEXTURE_2D)
    , aspect_(glm::vec2{0.f, 0.f})
    , size_({})
{
    //Register a 2D texture id
    glGenTextures(1, &name_);
}

GLTexture::GLTexture(std::string file)
    : GLTexture()
{
    load(file);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &name_);
}

void GLTexture::load(std::string file)
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

        /*fipImage resized(FIT_BITMAP, p2w, p2h, 32);
        if(not resized.pasteSubImage(image, 0, 0))
        {
            std::string err = "Failed to resize " + file;
            throw std::runtime_error(err);
        }*/

        const uint8_t* pixels = image.accessPixels();

        /*
        // Need to store the ratio between resized texture and original
        aspect_ = glm::vec2{static_cast<float>(p2w) / static_cast<float>(size_.x),
                            static_cast<float>(p2h) / static_cast<float>(size_.y)};
                            */

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

void GLTexture::bind(GLTexture const* t)
{
    if(t)
    {
        glBindTexture(t->target_, t->name_);
    }
}

void GLTexture::unbind(GLTexture const* t)
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
