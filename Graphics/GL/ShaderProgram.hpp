#ifndef TANK_GL_SHADERPROGRAM_HPP
#define TANK_GL_SHADERPROGRAM_HPP

#include <string>
#include <vector>
#include <GL/glew.h>

#include <glm/glm.hpp>

namespace tank {
namespace gl {

class ShaderProgram
{
public:
    static void bind(ShaderProgram*);
    static void unbind();

    enum Type { Vertex,
                Fragment };

    ShaderProgram();
    ShaderProgram(std::string file, Type type);
    ShaderProgram(std::string vertexShader, std::string fragmentShader);
    virtual ~ShaderProgram();

    void loadFromFile(std::string file, Type type);

    void loadFromFile(std::string vertexShader,
                      std::string fragmentShader);

    void loadFromSource(char const* source, Type type);

    void loadFromSource(char const* vertexShader,
                        char const* fragmentShader);

    void setUniform(std::string, GLint)            const;
    void setUniform(std::string, GLuint)           const;
    void setUniform(std::string, GLfloat)          const;
    void setUniform(std::string, glm::vec2 const&) const;
    void setUniform(std::string, glm::vec3 const&) const;
    void setUniform(std::string, glm::vec4 const&) const;
    void setUniform(std::string, glm::mat4 const&) const;

    GLuint name()    const { return program_; }
    bool   isValid() const { return valid_; }
private:
    void   createProgram();
    std::string loadSourceFromFile(std::string file);
    GLuint compileShaderFromSource(char const*, Type type);
    void   linkProgram(std::vector<GLuint> const& shaderObjects);

    GLuint program_;
    bool   valid_;

    ShaderProgram& operator=(ShaderProgram const&);
    ShaderProgram(ShaderProgram const&);
};

}
}
#endif /* TANK_GL_SHADERPROGRAM_HPP */
