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

#include "Buffer.hpp"

namespace tank {
namespace gl {

Buffer::Buffer(GLenum target)
    : target_(target)
{
    glGenBuffers(1, &name_);
}

Buffer::~Buffer()
{
    if(glIsBuffer(name_))
    {
        glDeleteBuffers(1, &name_);
    }
}

void Buffer::bind(Buffer const* b)
{
    if(b)
    {
        glBindBuffer(b->target_, b->name_);
    }
}

void Buffer::unbind(Buffer const* b)
{
    if(b)
    {
        glBindBuffer(b->target_, 0);
    }
}

}
}
