#include "Image.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

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
        shader_.reset(new GLShaderProgram("src/Engine/default.vert", "src/Engine/default.frag"));
    }

    if(buffer_.get() == nullptr)
    {
        float verts[] = {
            -1.f, -1.f, //v0
             1.f, -1.f, //v1
             1.f,  1.f, //v2
            -1.f,  1.f  //v3
        };

        buffer_.reset(new GLBuffer(GL_ARRAY_BUFFER));

        buffer_->setData(&verts, sizeof(verts), GL_STATIC_DRAW);
    }
}
Image::Image(std::string file)
    : Image()
{
    load(file);
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
    GLShaderProgram::bind(shader_.get()); 
    GLBuffer::bind(buffer_.get());
    GLTexture::bind(texture_.get());

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    GLTexture::unbind(texture_.get());
    GLBuffer::unbind(buffer_.get());
    GLShaderProgram::unbind();
}

}
