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
 * \brief This stores a transformation.
 */
class Transform
{
    // Order of operations on vector x is Z(O(R(x))), Z-zoom, O-offset,
    // R-rotation
    float rotation_ = 0.0f;
    Vectorf offset_ = {0.0f,0.0f};
    float zoom_ = 1.0f;

    // This is incase a graphic is involved, this is ignored for most purposes.
    Vectorf scale_ = {1.0f, 1.0f};

    friend class CoordinateSystem;
    friend class GraphicalCoordinateSystem;

public:
    Transform() = default;
    Transform(Vectorf const& offset);
    Transform(float rotation);
    Transform(float rotation, Vectorf const& offset);
    Transform(float rotation, Vectorf const& offset, float zoom);
    Transform(float rotation, Vectorf const& offset, float zoom, Vectorf scale);

    float getRotation() const
    {
        return rotation_;
    }
    Vectorf getOffset() const
    {
        return offset_;
    }
    float getZoom() const
    {
        return zoom_;
    }
    Vectorf getScale() const
    {
        return scale_;
    }

    void setRotation(float rotation)
    {
        rotation_ = rotation;
    }
    void setOffset(Vectorf const& offset)
    {
        offset_ = offset;
    }
    void setZoom(float zoom)
    {
        zoom_ = zoom;
    }
    void setScale(Vectorf const& scale)
    {
        scale_ = scale;
    }

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
