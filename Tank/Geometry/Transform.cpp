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
    t.setScale({zoom,zoom});
    t.setPosition({position.x, position.y});
    t.setRotation(rotation);
}

Vectorf Transform::operator()(Vectorf const& vec) const
{
    Vectorf rot = vec.rotate(rotation);
    return {zoom * rot.x + position.x,
            zoom * rot.y + position.y};
}

Transform Transform::operator()(Transform const& t) const
{
    // This works so that T'(T)(x) =  T'(T(x))
    auto tPos = t.position;
    tPos -= origin;
    tPos = tPos.rotate(rotation);
    tPos += origin;
    tPos *= zoom;

    return Transform{position + tPos,
                     rotation + t.rotation,
                     t.origin,
                     zoom * t.zoom};
}

Transform Transform::inverse() const
{
    Vectorf pos = -position.rotate(-rotation);
    return {pos/zoom, -rotation, 1/zoom};
}

} // tank
