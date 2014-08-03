// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Transform.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace tank
{

void Transform::transform(sf::Transformable& t) const
{
    // Change the setting of the transformable
    t.setScale({scale.x, scale.y});
    t.setPosition({position.x, position.y});
    t.setRotation(rotation);
}

Vectorf Transform::operator()(Vectorf const& vec) const
{
    Vectorf rot = vec.rotate(rotation);
    return {scale.x * rot.x + position.x,
            scale.y * rot.y + position.y};
}

Transform Transform::operator()(Transform const& t) const
{
    // This works so that T'(T)(x) =  T'(T(x))
    auto tPos = t.position.rotate(rotation);
    return Transform{position + Vectorf{scale.x * tPos.x, scale.y * tPos.y},
                     rotation + t.rotation,
                     origin + t.origin, // TODO: check this makes sense
                     {scale.x * t.scale.x, scale.y * t.scale.y}};
    /*
    return Transform{position + zoom * t.position.rotate(rotation),
                     rotation + t.rotation,
                     origin + t.origin, // TODO: check this makes sense
                     zoom * t.zoom,
                     {scale.x * t.scale.x, scale.y * t.scale.y}};
    */
}

Transform Transform::inverse() const
{
    Vectorf pos = -position.rotate(-rotation);
    return {{pos.x/scale.x, pos.y/scale.y}, -rotation, {1/scale.x, 1/scale.y}};
}

} // tank
