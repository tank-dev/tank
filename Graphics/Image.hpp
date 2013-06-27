#ifndef TANK_IMAGE_HPP
#define TANK_IMAGE_HPP

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "../Utility/Vector.hpp"
#include "GL/Texture.hpp"
#include "GL/Buffer.hpp"
#include "GL/ShaderProgram.hpp"
#include "Graphic.hpp"

namespace tank {

class Image final : public Graphic
{
public:
    Image();
    Image(std::string file);
    virtual ~Image();

    void load(std::string file);

    virtual Vectorf getSize() const override;
    void setSize(Vectorf const& size);

    virtual void draw(Vectorf const& pos, float angle = 0, Vectorf const& camera = {}) override;
private:
    GLuint vao_;
    bool loaded_;
    Vectorf size_;
    std::unique_ptr<gl::Texture> texture_;
    static std::unique_ptr<gl::Buffer>        buffer_;
    static std::unique_ptr<gl::ShaderProgram> shader_;
    static glm::mat4 projection_;

    Image& operator=(Image const&);
    Image(Image const&);
};

}
#endif /* TANK_IMAGE_HPP */
