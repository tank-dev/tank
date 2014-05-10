// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Transform.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace tank
{

Transform::Transform(Vectorf const& offset)
    : offset_(offset)
{}

Transform::Transform(float rotation)
    : rotation_(rotation)
{}

Transform::Transform(float rotation, Vectorf const& offset)
    : rotation_(rotation)
    , offset_(offset)
{}

Transform::Transform(float rotation, Vectorf const& offset, float zoom)
    : rotation_(rotation)
    , offset_(offset)
    , zoom_(zoom)
{}

Transform::Transform(float rotation,
                     Vectorf const& offset,
                     float zoom,
                     Vectorf scale)
    : rotation_(rotation)
    , offset_(offset)
    , zoom_(zoom)
    , scale_(scale)
{}

void Transform::transform(sf::Transformable& t) const
{
    // Change the setting of the transformable
    t.setScale({scale_.x * zoom_, scale_.y * zoom_});
    t.setPosition({offset_.x, offset_.y});
    t.setRotation(rotation_);
}

Vectorf Transform::operator()(Vectorf const& vec) const
{
    Vectorf rot = vec.rotate(rotation_);
    return {zoom_ * (rot.x + offset_.x) * scale_.x,
            zoom_ * (rot.y + offset_.y) * scale_.y};
}

Transform Transform::operator()(Transform const& t) const
{
    // This works so that T'(T)(x) =  T'(T(x))
    return Transform(rotation_ + t.rotation_,
                     offset_ + t.offset_.rotate(rotation_),
                     zoom_ * t.zoom_,
                     t.scale_);
}

Transform Transform::inverse() const
{
    return Transform(-rotation_, -offset_.rotate(-rotation_), 1/zoom_);
}

} // tank
