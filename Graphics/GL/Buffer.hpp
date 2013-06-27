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
