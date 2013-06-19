#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "../Utility/Vector.hpp"

class Texture
{
public:
    Vectori const& getSize() const { return size_; }

    Texture(GLenum target = GL_TEXTURE_RECTANGLE);
    Texture(std::string file, GLenum target = GL_TEXTURE_RECTANGLE);
    ~Texture();

    void load(std::string file);

    static void bind(Texture*);
    static const unsigned int bytesPerPixel = 4;
private:
    GLuint name_;

    bool loaded_;
    GLuint target_;

    Vectori size_;
};
#endif /* TANK_TEXTURE_HPP */
