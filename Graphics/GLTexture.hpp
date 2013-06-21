#ifndef TANK_GLTEXTURE_HPP
#define TANK_GLTEXTURE_HPP

#include <string>
#include <GL/glew.h>
#include "../Utility/Vector.hpp"

namespace tank {

class GLTexture
{
public:
    Vectori const& getSize() const { return size_; }

    GLTexture();
    GLTexture(std::string file);
    ~GLTexture();

    void load(std::string file);

    static void bind(GLTexture const*);
    static void unbind(GLTexture const*);
private:
    GLuint name_;

    bool loaded_;
    GLuint target_;

    Vectori size_;

    GLTexture(GLTexture const&);
    GLTexture& operator=(GLTexture const&);
};

}
#endif /* TANK_TEXTURE_HPP */
