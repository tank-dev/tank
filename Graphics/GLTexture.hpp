#ifndef TANK_GLTEXTURE_HPP
#define TANK_GLTEXTURE_HPP

#include <string>
#include <cstdint>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Utility/Vector.hpp"

namespace tank {

class GLTexture
{
public:
    GLTexture();
    GLTexture(std::string file);
    ~GLTexture();

    void load(std::string file);
    glm::vec2 const& aspect() const { return aspect_; }
    Vector<unsigned int> const& getSize() const { return size_; }
    bool isLoaded() const { return loaded_; }
    static void bind(GLTexture const*);
    static void unbind(GLTexture const*);
private:
    bool loaded_;
    //uint8_t* pixels_;

    GLuint name_;
    GLenum target_;

    glm::vec2 aspect_;
    Vector<unsigned int> size_;

    GLTexture(GLTexture const&);
    GLTexture& operator=(GLTexture const&);
};

}
#endif /* TANK_TEXTURE_HPP */
