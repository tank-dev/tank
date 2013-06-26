#include "Image.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../System/Game.hpp"

namespace tank {

std::unique_ptr<GLBuffer> Image::buffer_ { nullptr };
std::unique_ptr<GLShaderProgram> Image::shader_ { nullptr };

//TODO: Move somewhere it can be set by window resizing
glm::mat4 Image::projection_ = glm::ortho(0.f, 640.f, 640.f, 0.f, -1.f, 1.f);

Image::Image()
    : loaded_(false)
    , texture_(nullptr)
{
    if(shader_.get() == nullptr)
    {
        //TODO: CHANGE THIS TO MAKE IT NOT TERRIBLE
        shader_.reset(new GLShaderProgram("shaders/default.vert",
                                          "shaders/default.frag"));
    }

    if(buffer_.get() == nullptr)
    {
        float const verts[] = {
            0.f, 0.f, //v0
            1.f, 0.f, //v1
            1.f, 1.f, //v2
            0.f, 1.f  //v3
        };

        float const tex[] = {
            0.f, 0.f,
            1.f, 0.f,
            1.f, 1.f,
            0.f, 1.f
        };

        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        buffer_.reset(new GLBuffer(GL_ARRAY_BUFFER));

        buffer_->setData((void*)nullptr, sizeof(verts) + sizeof(tex), GL_STATIC_DRAW);
        buffer_->setSubData(&verts, sizeof(verts), sizeof(tex));
        buffer_->setSubData(&tex, sizeof(tex), 0);

        GLuint vertPos = glGetAttribLocation(shader_->name(), "v_pos");
        GLuint texPos = glGetAttribLocation(shader_->name(), "v_tex_pos");

        glVertexAttribPointer(vertPos,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              ((GLvoid*)sizeof(tex)));
        glVertexAttribPointer(texPos,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              ((GLvoid*)0));

        glEnableVertexAttribArray(vertPos);
        glEnableVertexAttribArray(texPos);
    }
}

Image::Image(std::string file)
    : Image()
{
    load(file);
}

void Image::load(std::string file)
{
    if(not loaded_)
    {
        texture_.reset(new GLTexture(file));

        size_.x = texture_->getSize().x;
        size_.y = texture_->getSize().y;

        loaded_ = true;
    }
}

void Image::draw(Vectorf const& pos, float angle, Vectorf const& camera)
{
    //TODO: Put int overloads in GLShaderObject
    //TODO: Move axis of rotation to global const
    GLShaderProgram::bind(shader_.get());
    GLTexture::bind(texture_.get());
    glBindVertexArray(vao_);

    // Set up model transform
    glm::mat4 viewTRS = glm::translate(glm::mat4(1.f),
                                       glm::vec3{camera.x, camera.y, 0.f});

    glm::mat4 modelT = glm::translate(glm::mat4(1.f),
                                      glm::vec3{pos.x, pos.y, 0.f});
    glm::mat4 modelTR = glm::rotate(modelT, angle, glm::vec3{ 0.f, 0.f, 1.f });
    glm::mat4 modelTRS = glm::scale(modelTR,
                                    glm::vec3{10*size_.x, 10*size_.y, 1.f});

    glm::mat4 pvm = projection_ * viewTRS * modelTRS;
    shader_->setUniform("pvm", pvm);

    // YAY WE GET TO DRAW
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
    GLTexture::unbind(texture_.get());
    GLShaderProgram::unbind();
}

Image::~Image()
{
    glDeleteVertexArrays(1,&vao_);
}

Vectorf Image::getSize() const
{
    return size_;
}

void Image::setSize(Vectorf const& size)
{
    size_ = size;
}

}
