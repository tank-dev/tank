#include "GLTexture.hpp"

#include <SFML/OpenGL.hpp>
#include <CImg.h>
#include <cstdint>

/* TODO:
 *   * Allow mipmaps
 *   * Allow different data formats
 *   * Allow multisampling
 */

GLTexture::GLTexture()
    : loaded_(false)
    , target_(GL_TEXTURE_RECTANGLE)
{
    //Register a 2D texture id

    glGenTextures(1, &name_);
    glBindTexture(target_, name_);
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
    if(!loaded_)
    {
        cimg_library::CImg<float> texture(file.c_str());

        size_.x = texture.width(),
        size_.y = texture.height();

        float* pixels = texture.data();

        glBindTexture(target_, name_);

        glTexStorage2D(target_, 1, GL_RGBA8, size_.x, size_.y);

        glTexSubImage2D(target_, 0,
                        0, 0,
                        size_.x, size_.y,
                        GL_RGBA8,
                        GL_FLOAT,
                        pixels);

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
