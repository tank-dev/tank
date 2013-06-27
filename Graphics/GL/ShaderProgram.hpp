/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

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
