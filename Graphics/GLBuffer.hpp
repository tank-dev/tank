#ifndef TANK_GLBUFFER_HPP
#define TANK_GLBUFFER_HPP

#include <GL/glew.h>

namespace tank {
//TODO: SubBufferData
class GLBuffer
{ 
public:
    GLBuffer(GLenum target);
    ~GLBuffer();

    template <typename T>
    void setData(T* data, size_t size, GLenum mode);
    
    template <typename T>
    void setSubData(T* data, size_t size, size_t offset);

    static void bind(GLBuffer const*);
    static void unbind(GLBuffer const*);
private:
    GLuint target_;
    GLuint name_;
};

template <typename T>
void GLBuffer::setData(T* data, size_t size, GLenum mode)
{
    bind(this);
    glBufferData(target_, size, data, mode);
}
    
template <typename T>
void GLBuffer::setSubData(T* data, size_t size, size_t offset)
{ 
    bind(this);
    glBufferSubData(target_, offset, size, data);
}
}
#endif /* TANK_GLBUFFER_HPP */
