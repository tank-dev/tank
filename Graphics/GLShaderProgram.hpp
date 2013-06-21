#ifndef TANK_GLSHADERPROGRAM_HPP
#define TANK_GLSHADERPROGRAM_HPP

#include <string>
#include <vector>
#include <GL/glew.h>

#include <glm/glm.hpp>

class GLShaderProgram
{
public:
    static void bind(GLShaderProgram*);

    enum Type { Vertex,
                Fragment };

    GLShaderProgram();
    GLShaderProgram(std::string file, Type type);
    GLShaderProgram(std::string vertexShader, std::string fragmentShader);
    virtual ~GLShaderProgram();

    void loadFromFile(std::string file, Type type);

    void loadFromFile(std::string vertexShader,
                      std::string fragmentShader);

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
    GLuint compileShaderFromFile(std::string file, Type type);
    void   compileProgram(std::vector<GLuint> const& shaderObjects);

    GLuint program_;
    bool   valid_;

    GLShaderProgram& operator=(GLShaderProgram const&);
    GLShaderProgram(GLShaderProgram const&);
};
#endif /* TANK_SHADERPROGRAM_HPP */
