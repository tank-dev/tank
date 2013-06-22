#include "Image.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../System/Game.hpp"

namespace tank {

std::unique_ptr<GLBuffer> Image::buffer_ { nullptr };
std::unique_ptr<GLShaderProgram> Image::shader_ { nullptr };

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
            -1.f, -1.f, //v0
             1.f, -1.f, //v1
             1.f,  1.f, //v2
            -1.f,  1.f  //v3
        };

        float const tex[] = {
            0.f, 0.f,
            1.f, 0.f,
            1.f, 1.f,
            0.f, 1.f
        };

        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        Game::log << "Loading buffer data" << std::endl;
        buffer_.reset(new GLBuffer(GL_ARRAY_BUFFER));

        buffer_->setData((void*)NULL, sizeof(verts) + sizeof(tex), GL_STATIC_DRAW);
        buffer_->setSubData(&verts, sizeof(verts), 0);
        buffer_->setSubData(&tex, sizeof(tex), sizeof(verts));

        GLuint vertPos = glGetAttribLocation(shader_->name(), "pos");
        glVertexAttribPointer(vertPos, 2, GL_FLOAT, GL_FALSE, 0, ((GLvoid*)0));

        GLuint texPos = glGetAttribLocation(shader_->name(), "tPos");
        glVertexAttribPointer(texPos, 2, GL_FLOAT, GL_FALSE, 0, ((GLvoid*)sizeof(verts)));

        glEnableVertexAttribArray(vertPos);
        glEnableVertexAttribArray(texPos);
    }
}
Image::Image(std::string file)
    : Image()
{
    load(file);
}

Image::~Image()
{
    glDeleteVertexArrays(1,&vao_);
}

Vectorf Image::getSize() const
{
    return halfSize_ * 2.f;
}

void Image::setSize(Vectorf const& size)
{
    halfSize_ = size / 2.f;
}

void Image::load(std::string file)
{
    if(not loaded_)
    {
        texture_.reset(new GLTexture(file));

        halfSize_.x = texture_->getSize().x / 2;
        halfSize_.y = texture_->getSize().y / 2;

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
    //Set up model transform
    glm::mat4 modelS(1.f);
    glm::mat4 modelRS = glm::rotate(modelS, angle, glm::vec3{ 0.f, 0.f, 1.f });
    glm::mat4 modelTRS = glm::translate(modelRS, glm::vec3{pos.x, pos.y, 0.f});

    shader_->setUniform("modelTransform", modelTRS);

    //Set up view transform
    glm::mat4 viewTRS = glm::translate(glm::mat4(1.f),
                                       glm::vec3{camera.x, camera.y, 0.f});
    shader_->setUniform("viewTransform", viewTRS);

    //Send Image size to shader
    shader_->setUniform("halfImgSize", glm::vec2{halfSize_.x, halfSize_.y});

    //Send window size to shader
    shader_->setUniform("viewportSize", glm::vec2 {
                             static_cast<float>(Game::window().getSize().x),
                             static_cast<float>(Game::window().getSize().y)});

    //YAY WE GET TO DRAW
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
    GLTexture::unbind(texture_.get());
    GLShaderProgram::unbind();
}

}
