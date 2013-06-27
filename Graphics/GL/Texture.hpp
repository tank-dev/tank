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

#ifndef TANK_GLTEXTURE_HPP
#define TANK_GLTEXTURE_HPP

#include <string>
#include <cstdint>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../../Utility/Vector.hpp"

namespace tank {
namespace gl {

class Texture
{
public:
    Texture();
    Texture(std::string file);
    ~Texture();

    void load(std::string file);
    glm::vec2 const& scale() const { return scale_; }
    Vector<unsigned int> const& getSize() const { return size_; }
    bool isLoaded() const { return loaded_; }
    static void bind(Texture const*);
    static void unbind(Texture const*);
private:
    bool loaded_;
    //uint8_t* pixels_;

    GLuint name_;
    GLenum target_;

    glm::vec2 scale_;
    Vector<unsigned int> size_;

    Texture(Texture const&);
    Texture& operator=(Texture const&);
};

}
}
#endif /* TANK_TEXTURE_HPP */
