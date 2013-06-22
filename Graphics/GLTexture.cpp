#include "GLTexture.hpp"

#include <SFML/OpenGL.hpp>
#include <CImg.h>
#include <cstdint>
#include "../System/Game.hpp"

namespace tank {
/* TODO:
 *   * Allow mipmaps
 *   * Allow different data formats
 *   * Allow multisampling
 */

GLTexture::GLTexture()
    : loaded_(false)
    , target_(GL_TEXTURE_2D)
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
        //TODO: Exception this up
        Game::log << "Loading texture from file" << std::endl;
        cimg_library::CImg<float> texture(file.c_str());
        Game::log << "Texture loaded" << std::endl;

        size_.x = texture.width(),
        size_.y = texture.height();

        float* pixels = texture.data();
        glBindTexture(target_, name_);

        glTexStorage2D(target_, 0, GL_RED, size_.x, size_.y);

        glTexSubImage2D(target_, 0,
                        0, 0,
                        size_.x, size_.y,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
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

}
