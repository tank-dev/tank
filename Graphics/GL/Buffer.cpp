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
