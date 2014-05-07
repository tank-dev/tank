// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_FRAMELIST_HPP
#define TANK_FRAMELIST_HPP

#include <string>
#include <vector>
#include <functional>
#include "Graphic.hpp"
#include "Image.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/Timer.hpp"

namespace tank
{

/*!
 * \brief Represents an image with multiple frames and stores animations for
 * that image.
 */
class FrameList final : public Image
{
    struct Animation
    {
        std::string name;
        std::vector<unsigned int> frameList;
        std::chrono::milliseconds time;
    };

    Animation* currentAnimation_ {nullptr};
    unsigned int currentFrame_ {0};
    Timer animTimer_;
    bool loop_ {false};
    Vectoru frameDimensions_ {0, 0};
    Rectu clipRect_ {0,0,0,0};
    /*!
     * \brief This is called when an animation finishes
     */
    std::function<void()> callback_ = []{};
    std::vector<Animation>  animations_;

public:
    FrameList() = default;
    /*!
     * \brief Construct an Animation with a Texture.
     * \param file the file to load the texture from.
     * \param frameDims size of each image in the Texture.
     */
    FrameList(std::string file, Vector<unsigned int> frameDimensions);

    /*!
     * \brief Add an animation
     *
     * Create a named list of frames to play in sequence, to be displayed  at a
     * fixed rate
     *
     * \param name String to identify the animation with later.
     * \param frames std::initializer_list of frames.
     * \param frameTime Time between each frame in milliseconds (ms)
     */
    void add(std::string name, const std::vector<unsigned int>& frames,
             std::chrono::milliseconds frameTime);

    /*!
     * \brief Removes an animation.
     *
     * \param name Animation to remove.
     */
    void remove(std::string name);

    /*!
     * \brief Selects an animation to play
     *
     * \param name Animation to play.
     * \param loop If the animation should loop, defaults to true.
     * \param callback A function to be called when the animation finishes.
     */
    void select(std::string name, bool loop = true,
                std::function<void()> callback = []{});

    /*!
     * \brief Update the animation to the current frame. Called by draw
     */
    void refresh();

    /*!
     * \brief Start the animation
     */
    void start();

    /*!
     * \brief Pause the animation.
     */
    void pause();

    /*!
     * \brief Resume the animation.
     */
    void resume();

    /*!
     * \brief Stop the animation.
     * Sets the state of the animation to the first frame.
     */
    void stop();

    /*!
     * \return If the animation is playing.
     */
    bool playing()
    {
        return currentAnimation_;
    }
    std::string currentAnimation()
    {
        if (not playing())
        {
            return "";
        }
        return currentAnimation_->name;
    }

    /*!
     * \brief Set the dimensions of the image in the texture.
     *
     * \param frameDims the dimensions of each image in the texture.
     */
    void setFrameDimensions(Vectoru frameDims)
    {
        frameDimensions_ = frameDims;
    }

    Vectoru getFrameDimensions() const { return frameDimensions_; }

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
    virtual void setClip(Vectoru dimensions, unsigned int index, Rectu clip = {0,0,0,0}) override;

    /*!
     * \brief Sets the clip rectangle of the image
     *
     * \param clip The rectangle to clip the image to
     */
    virtual void setClip(Rectu clip) override
    {
        clipRect_ = clip;
    }
    virtual Rectu getClip() const
    {
        return clipRect_;
    }

    // We are not overriding draw(Transform) as at that point there is no way
    // to call refresh
    /*!
     * \brief Draw the animation.
     *
     * Trying to draw an animation without a texture will crash the game!
     *
     * \param pos Position at which to draw the texture.
     */
    virtual void draw(Camera const* cam = nullptr) override;
};

// TODO: Use enum to specify image format
/*!
 * \brief Generate a walking animations for Animation
 *
 * Generates four animations: walk_up, walk_right, walk_down, walk_left.
 * Currently, they are generated from image rows going down in that order.
 */
void addWalkingAnimation(FrameList& frames, std::chrono::milliseconds time);

} // tank

#endif /* TANK_FRAMELIST_HPP */
