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
    void setData(T* data, size_t size, GLenum mode)
    {
        bind(this);
        glBufferData(target_, size, data, mode);
        unbind(this);
    }
    static void bind(GLBuffer const*);
    static void unbind(GLBuffer const*);
private:
    GLuint target_;
    GLuint name_;
};

}
#endif /* TANK_GLBUFFER_HPP */
