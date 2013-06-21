#include "GLBuffer.hpp"

GLBuffer::GLBuffer(GLenum target)
    : target_(target)
{ 
    glGenBuffers(1, &name_);
}

GLBuffer::~GLBuffer()
{
    if(glIsBuffer(name_))
    {
        glDeleteBuffers(1, &name_);
    }
}

void GLBuffer::bind(GLBuffer const* b)
{
    if(b)
    {
        glBindBuffer(b->target_, b->name_);
    }
}

void GLBuffer::unbind(GLBuffer const* b)
{
    if(b)
    {
        glBindBuffer(b->target_, 0);
    }
}
