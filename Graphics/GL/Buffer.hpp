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

#ifndef TANK_GL_BUFFER_HPP
#define TANK_GL_BUFFER_HPP

#include <GL/glew.h>

namespace tank {
namespace gl {

class Buffer
{
public:
    Buffer(GLenum target);
    ~Buffer();

    template <typename T>
    void setData(T* data, size_t size, GLenum mode);

    template <typename T>
    void setSubData(T* data, size_t size, size_t offset);

    static void bind(Buffer const*);
    static void unbind(Buffer const*);
private:
    GLuint target_;
    GLuint name_;
};

template <typename T>
void Buffer::setData(T* data, size_t size, GLenum mode)
{
    bind(this);
    glBufferData(target_, size, data, mode);
}

template <typename T>
void Buffer::setSubData(T* data, size_t size, size_t offset)
{
    bind(this);
    glBufferSubData(target_, offset, size, data);
}

}
}
#endif /* TANK_GL_BUFFER_HPP */
