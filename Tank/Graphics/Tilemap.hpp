// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TILEMAP_HPP
#define TANK_TILEMAP_HPP

#include "Graphic.hpp"
#include "Image.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/Grid.hpp"
#include "../Utility/CollisionGrid.hpp"

#include <string>
#include <functional>
#include <vector>

namespace tank
{

/*!
 * \brief This is a tilemap.
 */
class Tilemap final : public Graphic
{
    Image image_;
    Vectoru frameDimensions_{0, 0};
    Rectu clipRect_{0, 0, 0, 0};
    Grid<unsigned> tiles_;

public:
    /*!
     * \brief Constructs a tilemap, a texture will need to be loaded and the
     * tile and grid dimensions will have to set before it can be used.
     */
    Tilemap() = default;
    /*!
     * \brief Construct an Tilemap with a Texture.
     *
     * \param file the file to load the texture from.
     * \param gridDims size of the grid.
     * \param frameDims size of each image in the Texture.
     */
    Tilemap(Image const& img,
            Vector<unsigned> gridDims,
            Vector<unsigned int> frameDims);

    /*!
     * \brief Draw the animation.
     *
     * Trying to draw an animation without a texture will crash the game!
     *
     * \param pos Position at which to draw the texture.
     */
    virtual void draw(Transform const& t) override;

    /*!
     * \brief Set the texture of the Tilemap.
     * \param image the Texture to set.
     * \param frameDimensions the dimensions of the sprite to animate
     */
    void setImage(Image const& image,
                  Vectoru frameDimensions,
                  Vectoru spacing = {},
                  Rectu subClip = {});
    /*!
     * \brief Set the dimensions of the image in the texture.
     *
     * \param frameDims the dimensions of each image in the texture.
     */
    void setFrameDimensions(Vectoru frameDims)
    {
        frameDimensions_ = frameDims;
        clipRect_ = {0, 0, frameDims.x, frameDims.y};
    }

    Vectoru getFrameDimensions() const
    {
        return frameDimensions_;
    }
    Vectorf getTileDimensions() const
    {
        return { getClip().w * getZoom() * getScale().x, getClip().h * getZoom() * getScale().y};
    }

    virtual Vectorf getSize() const override
    {
        Vectorf size = getTileDimensions();
        return {size.x * tiles_.getWidth(), size.y * tiles_.getHeight()};
    }

    /*!
     * \brief This sets the clip rectangle by tiling the region and selecting
     * the tile designated by index. It has an option of setting an additional
     * clip within that area.
     *
     * \param dimensions The dimensions of the tile.
     * \param index The index of the tile to select.
     * \param clip An optional parameter for additional clipping within the
     * designated area.
     */
    /*
    // TODO: work out what anstow's doing here
    //
    // anstow: Was the description above not sufficient?
    virtual void setClipByIndex(Vectoru dimensions, unsigned int index,
                         Vectoru spacong = {}, Rectu subClip = {}) override;
     */

    /*!
     * \brief Sets an internal clip rectangle for each tile
     *
     * \param clip The rectangle to clip each tile to, defaults to using the
     * entire frame
     */
    // TODO: work out what anstow's doing here
    //
    // anstow: If I rememeber correctly this was to allow an internal clip
    // rectangle, I believe this is superceeded by your subClip or perhaps used
    // with it? Assuming I've understood it correctly.
    virtual void setClip(Rectu clip = {})
    {
        clipRect_ = clip;
    }
    virtual Rectu getClip() const
    {
        if (clipRect_ == Rectu{})
        {
            return image_.getClip();
        }
        else 
        {
            return clipRect_;
        }
    }

    /*!
     * \brief This gets the tile position from the local coordinates.
     *
     * It fail silently, so don't forget to check that the point is within the
     * bounds of the shape using checkWithin.
     *
     * \param localCoords The point to convert into tile coordinates.
     *
     * \return The tile coordinates of the specified point.
     */
    Vectoru getTile(const Vectorf& localCoords);

    CollisionGrid
            getCollisionGrid(const std::unordered_set<unsigned>& collidable)
    {
        return CollisionGrid(tiles_, collidable);
    }

    /*!
     * \brief This sets the grid to be used for this tilemap.
     *
     * \param grid The grid to be used for the tilemap.
     */
    void setGrid(Grid<unsigned> const& grid)
    {
        tiles_ = grid;
    }

    /*!
     * \brief This sets a line in the Tilemap
     *
     * \param start The start of the line to set
     * \param end The end of the line to set
     * \param value The value to set the line to
     */
    void setLine(const Vectoru& start, const Vectoru& end, unsigned value)
    {
        tiles_.setLine(start, end, value);
    }
    /*!
     * \brief This fills a box in the Tilemap with the specifed value
     *
     * \param start One corner of the box
     * \param end The diagonal cormer to the box
     * \param value The value to set
     */
    void fillBox(const Vectoru& start, const Vectoru& end, unsigned value)
    {
        tiles_.fillBox(start, end, value);
    }
    /*!
     * \brief This outlines a box in the Tilemap with the specifed value
     *
     * \param start One corner of the box
     * \param end The diagonal cormer to the box
     * \param value The value to set
     */
    void outlineBox(const Vectoru& start, const Vectoru& end, unsigned value)
    {
        tiles_.outlineBox(start, end, value);
    }
};

} // tank

#endif /* TANK_TILEMAP_HPP */
