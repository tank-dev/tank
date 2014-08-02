// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Transform.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace tank
{

Transform::Transform(Vectorf position,
                     float rotation,
                     Vectorf origin,
                     float zoom,
                     Vectorf scale)
    : position(position)
    , rotation(rotation)
    , origin(origin)
    , zoom(zoom)
    , scale(scale)
{}

void Transform::transform(sf::Transformable& t) const
{
    // Change the setting of the transformable
    t.setScale({scale.x * zoom, scale.y * zoom});
    t.setPosition({position.x, position.y});
    t.setRotation(rotation);
}

Vectorf Transform::operator()(Vectorf const& vec) const
{
    Vectorf rot = vec.rotate(rotation);
    return {zoom * scale.x * rot.x + position.x,
            zoom * scale.y * rot.y + position.y};
}

Transform Transform::operator()(Transform const& t) const
{
    // This works so that T'(T)(x) =  T'(T(x))
    return Transform{position + zoom * t.position.rotate(rotation),
                     rotation + t.rotation,
                     origin + t.origin, // TODO: check this makes sense
                     zoom * t.zoom,
                     {scale.x * t.scale.x, scale.y * t.scale.y}};
}

Transform Transform::inverse() const
{
    return {-position.rotate(-rotation)/zoom, -rotation, 1/zoom};
}

} // tank
