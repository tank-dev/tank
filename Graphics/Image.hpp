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
    //Image(Image const&);
    Image(std::string file);
    virtual ~Image();

    void load(std::string file);

    virtual void setOrigin(Vectorf);
    virtual Vectorf getOrigin() const;

    virtual Vectorf getSize() const override;
    void setSize(Vectorf size) override;

    virtual void setClip(Rect) override;
    virtual Rect getClip() const override;

    virtual void draw(Vectorf pos, float angle = 0, Vectorf camera = {}) override;
private:
    bool loaded_;
    Vectorf size_;
    glm::vec4 clip_;
    glm::vec2 origin_;
    std::shared_ptr<gl::Texture> texture_;

    static GLuint vao_;
    static std::unique_ptr<gl::Buffer>        buffer_;
    static std::unique_ptr<gl::ShaderProgram> shader_;
    static glm::mat4 projection_;

    Image& operator=(Image const&);
};

}
#endif /* TANK_IMAGE_HPP */
