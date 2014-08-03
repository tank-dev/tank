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
class FrameList final : public Graphic
{
    struct Animation
    {
        std::string name;
        std::vector<unsigned int> frameList;
        std::chrono::milliseconds time;
    };

    Image image_;
    Vectoru frameDimensions_ {0, 0};
    Vectoru spacing_ {};
    Rectu subClip_ {};
    Animation* currentAnimation_ {nullptr};
    unsigned int currentFrame_ {0};
    Timer animTimer_;
    bool loop_ {false};
    std::vector<Animation> animations_;
    std::function<void()> callback_ = [] {};

public:
    FrameList() = default;
    /*!
     * \brief Construct an Animation with a Texture.
     * \param t Image to give the animation.
     * \param frameDimensions size of each image in the Texture.
     */
    FrameList(Image const&,
              Vectoru frameDimensions,
              Vectoru spacing = {},
              Rectu subClip = {});

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
                std::function<void()> callback = [] {});

    /*!
     * \brief Update the animation to the current frame. Called by draw
     */
    void refresh();

    /*!
     * \brief Draw the animation.
     *
     * Trying to draw an animation without a texture will crash the game!
     *
     * \param pos Position at which to draw the texture.
     */
    virtual void draw() override;

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
    bool playing() { return currentAnimation_; }

    std::string currentAnimation()
    {
        if (not playing()) {
            return "";
        }
        return currentAnimation_->name;
    }

    /*!
     * \brief Set the texture of the FrameList.
     * \param image the Texture to set.
     * \param frameDimensions the dimensions of the sprite to animate
     */
    void setImage(Image const& image,
                  Vectoru frameDimensions,
                  Vectoru spacing = {},
                  Rectu subClip = {});

    void setSize(Vectorf size) { image_.setSize(size); }
    Vectorf getSize() const override { return image_.getSize(); }
    void setClip(Rectu clip) { image_.setClip(clip); }
    Rectu getClip() const { return image_.getClip(); }
    virtual Vectoru getTextureSize() const
    {
        return image_.getTextureSize();
    }

    Vectoru getFrameDimensions() const { return frameDimensions_; }
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
