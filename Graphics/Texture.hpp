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

    Texture();
    Texture(std::string file);
    ~Texture();

    void load(std::string file);

    static void bind(Texture*);
private:
    GLuint name_;

    bool loaded_;
    GLuint target_;

    Vectori size_;
};
#endif /* TANK_TEXTURE_HPP */
