#include "GLShaderProgram.hpp"

#include <iostream>
#include <stdexcept>
#include <fstream>

namespace tank {

void GLShaderProgram::bind(GLShaderProgram *shader)
{
    if(shader->valid_) glUseProgram(shader->program_);
}

GLShaderProgram::GLShaderProgram() : program_(0), valid_(true) { }

GLShaderProgram::GLShaderProgram(std::string file, Type type)
    :program_(0), valid_(false)
{
    loadFromFile(file,type);
}

GLShaderProgram::GLShaderProgram(std::string vertexShader,
               std::string fragmentShader)
    :program_(0), valid_(false)
{
    loadFromFile(vertexShader,fragmentShader);
}

GLShaderProgram::~GLShaderProgram()
{
    if(glIsProgram(program_))
    {
        glDeleteProgram(program_);
    }
}

/////////////////////////////////////////////
// Uniform Accessors
/////////////////////////////////////////////

void GLShaderProgram::setUniform(std::string name, GLint value) const
{
    GLuint addr = glGetUniformLocation(program_, name.c_str());

    glProgramUniform1i(program_, addr,value);
}

void GLShaderProgram::setUniform(std::string name, GLuint value) const
{
    GLuint addr = glGetUniformLocation(program_, name.c_str());

    glProgramUniform1ui(program_, addr,value);
}

void GLShaderProgram::setUniform(std::string name, GLfloat value)  const
{
    GLuint addr = glGetUniformLocation(program_, name.c_str());

    glProgramUniform1f(program_, addr,value);
}

void GLShaderProgram::setUniform(std::string name, glm::vec2 const& value) const
{
    GLuint addr = glGetUniformLocation(program_, name.c_str());

    glProgramUniform2fv(program_, addr, 1, &value[0]);
}

void GLShaderProgram::setUniform(std::string name, glm::vec3 const& value) const
{
    GLuint addr = glGetUniformLocation(program_, name.c_str());

    glProgramUniform3fv(program_, addr, 1, &value[0]);
}

void GLShaderProgram::setUniform(std::string name, glm::vec4 const& value) const
{
    GLuint addr = glGetUniformLocation(program_, name.c_str());

    glProgramUniform4fv(program_, addr, 1, &value[0]);
}

void GLShaderProgram::setUniform(std::string name, glm::mat4 const& value) const
{
    GLuint addr = glGetUniformLocation(program_, name.c_str());

    glProgramUniformMatrix4fv(program_, addr, 1, false, &value[0][0]);
}

/////////////////////////////////////////////
// Loading Functions
/////////////////////////////////////////////

void GLShaderProgram::loadFromFile(std::string file, Type type)
{
    createProgram();

    GLuint shaderObject = compileShaderFromFile(file, type);

    compileProgram({shaderObject});

    //If we made it here, must be valid
    valid_ = true;
}

void GLShaderProgram::loadFromFile(std::string vertexShader,
                          std::string fragmentShader)
{
    createProgram();

    GLuint vertexObject   = compileShaderFromFile(vertexShader,   Vertex);
    GLuint fragmentObject = compileShaderFromFile(fragmentShader, Fragment);

    compileProgram({vertexObject, fragmentObject});

    //If we made it here, must be valid
    valid_ = true;
}

void GLShaderProgram::createProgram()
{
    if(glIsProgram(program_))
    {
        glDeleteProgram(program_);
    }

    program_ = glCreateProgram();

    if(program_ == 0)
    {
        throw std::runtime_error("Could not create shader");
    }
}

GLuint GLShaderProgram::compileShaderFromFile(std::string file, Type type)
{
    GLuint shaderObject = 0;

    if(type == Vertex)
    {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }
    else if(type == Fragment)
    {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    if(shaderObject == 0)
    {
        throw std::runtime_error("Could not create shader.");
    }

    std::fstream f(file, std::ios::in);

    if(f.fail())
    {
        std::string error = "Could not open file \"";
        error.append(file);
        error.append("\"");
        std::cout << error << std::endl;
        throw std::runtime_error(error);
    }

    std::string content;
    while(!f.eof())
    {
        std::string line;
        std::getline(f, line);
        content.append(line + '\n');
    }
    f.close();

    const char* shaderSource = content.c_str();

    glShaderSource(shaderObject, 1, &shaderSource, NULL);

    glCompileShader(shaderObject);

    GLint status;
    glGetShaderiv(shaderObject,GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE)
    {
        char logText[1000];
        glGetShaderInfoLog(shaderObject, 1000, NULL, logText);

        std::ofstream logfile("compile_errors.txt",std::ios::out);

        if(!logfile.is_open())
        {
            throw std::runtime_error("ShaderProgram failed to compile. Could not open logfile");
        }

        logfile << logText << "\n";
        logfile << "Code:\n\n";
        logfile << file;
        logfile.close();

        std::string error = "ShaderProgram failed to compile (see compile_errors.txt): ";
        error.append(file);

        glDeleteShader(shaderObject);

        throw std::runtime_error(error);
    }

    return shaderObject;
}

void GLShaderProgram::compileProgram(std::vector<GLuint> const& shaderObjects)
{
    for(auto so : shaderObjects)
    {
        glAttachShader(program_, so);
    }

    glLinkProgram(program_);

    GLint status;
    glGetProgramiv(program_, GL_LINK_STATUS, &status);

    if(status != GL_TRUE)
    {
        char logText[1000];
        glGetProgramInfoLog(program_, 1000, NULL, logText);

        std::fstream logfile("link_errors.txt", std::ios::out);

        logfile << logText;
        logfile.close();
        std::string error = "Failed to link shader program. See link_errors.txt";

        for(auto so : shaderObjects)
        {
            glDeleteShader(so);
        }

        throw std::runtime_error(error);
    }

    for(auto so : shaderObjects)
    {
        glDeleteShader(so);
    }
}

}
