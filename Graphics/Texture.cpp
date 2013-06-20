#include "Texture.hpp"

#include <SFML/OpenGL.hpp>
#include <CImg.h>
#include <cstdint>

/* TODO:
 *   * Allow mipmaps
 *   * Allow different data formats
 *   * Allow multisampling
 */

Texture::Texture(GLenum target)
    : loaded_(false)
    , target_(target)
{
    //Register a 2D texture id

    glGenTextures(1, &name_);
    glBindTexture(target_, name_);
}

Texture::Texture(std::string file, GLenum target)
    : Texture(target)
{
    load(file);
}

Texture::~Texture()
{
    glDeleteTextures(1, &name_);
}

void Texture::load(std::string file)
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

void Texture::bind(Texture* t)
{
    GLuint name = t ? t->name_ : 0;

    glBindTexture(t->target_, name);
}
