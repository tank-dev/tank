#pragma once
#ifndef TANK_IMAGE_HPP
#define TANK_IMAGE_HPP

#include <string>
#include <memory>
#include "../Utility/Vector.hpp"
#include "GLTexture.hpp"
#include "Graphic.hpp"

class Image final : public Graphic
{
public:
    Image();
    //Image(GLTexture const&);
    Image(std::string file);
    virtual ~Image();

    //void load(GLTexture const&);
    void load(std::string file);

    virtual Vectori const& getSize() const;

    virtual void draw(Vectorf const& pos);
private:
    bool loaded_;
    std::unique_ptr<GLTexture> texture_;

    Image& operator=(Image const&);
    Image(Image const&);
};

#endif /* TANK_IMAGE_HPP */
