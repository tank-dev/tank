// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TRANSFORM_HPP
#define TANK_TRANSFORM_HPP

#include "../Utility/observing_ptr.hpp"
#include "../Utility/Vector.hpp"

namespace sf
{
    class Transformable;
}

namespace tank
{

/*!
 * \brief This stores a transformation. It is stored is 3 componenets; Zoom,
 * Position and Rotation. They are ordered so that the zoom and rotation are
 * applied first and then the position. (As this is the way SFML does it.)
 *
 * A scale compenent is also included but this is strictly for working with
 * graphics and full affine transformations aren't supported.
 */
struct Transform
{
    // Order of operations on vector x is O(Z(R(x))), Z-zoom, O-position,
    // R-rotation
    Vectorf position = {0.0f,0.0f};
    float rotation = 0.0f;
    Vectorf origin = {0.0f,0.0f};
    float zoom = 1.f;

    Transform(Vectorf position = {},
              float rotation = 0,
              Vectorf origin = {}, 
              float zoom = 1.f)
        : position(position)
        , rotation(rotation)
        , origin(origin)
        , zoom(zoom)
    {}
    Transform(Transform const&) = default;
    Transform& operator=(Transform const&) = default;

    /*!
     * \brief This applies the transform to a sprite.
     *
     * \param t The sprite apply the transform to.
     */
    void transform(sf::Transformable& t) const;

    /*!
     * \brief This applies the transformation to a point.
     *
     * \param vec The point to apply the transformation to.
     *
     * \return The transformed point.
     */
    Vectorf operator()(Vectorf const& vec) const;
    /*!
     * \brief This applies the transformation to another transformation,
     * composing the two.
     *
     * If T and T' are the transformations then this is such that T'(T)(x) =
     * T'(T(x)). It ignores the scale of the first transformation.
     *
     * \param t The transform to be applied to.
     *
     * \return The composed transformation.
     */
    Transform operator()(Transform const& t) const;

    /*!
     * \brief This gets the inverse transformation.
     * Note it ignores the scale property.
     *
     * \return The inverse transformation.
     */
    Transform inverse() const;
};

} // tank

#endif // TANK_TRANSFORM_HPP
