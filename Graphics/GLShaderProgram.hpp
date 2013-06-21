#ifndef TANK_SHADERPROGRAM_HPP
#define TANK_SHADERPROGRAM_HPP

#include <string> 
#include <vector>
#include <GL/glew.h>

#include <glm/glm.hpp>

class ShaderProgram
{
public:
    static void bind(ShaderProgram const&);

    enum Type { Vertex,
                Fragment };

    ShaderProgram();
    ShaderProgram(std::string const& file, Type type);
    ShaderProgram(std::string const& vertexShader, std::string const& fragmentShader);
    virtual ~ShaderProgram();

    void loadFromFile(std::string const& file, Type type);

    void loadFromFile(std::string const& vertexShader, 
                      std::string const& fragmentShader);

    void setUniform(std::string const&, GLint)            const;
    void setUniform(std::string const&, GLuint)           const;
    void setUniform(std::string const&, GLfloat)          const;
    void setUniform(std::string const&, glm::vec2 const&) const;
    void setUniform(std::string const&, glm::vec3 const&) const;
    void setUniform(std::string const&, glm::vec4 const&) const;
    void setUniform(std::string const&, glm::mat4 const&) const;

    GLuint name()    const { return program_; }
    bool   isValid() const { return valid_; } 
private: 
    void   createProgram();
    GLuint compileShaderFromFile(std::string const& file, Type type); 
    void   compileProgram(std::vector<GLuint> const& shaderObjects);

    GLuint program_;
    bool   valid_;

    ShaderProgram& operator=(ShaderProgram const&);
    ShaderProgram(ShaderProgram const&);
};
#endif /* TANK_SHADERPROGRAM_HPP */
