// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Mouse.hpp"
#include "../System/Entity.hpp"

namespace tank {

bool Mouse::stateChange_ {false};
Vectori Mouse::currentPos_;
Vectori Mouse::lastPos_;
// TODO: Could set this at Game::initialize?
Vectori Mouse::lockPos_ {5,5};
int Mouse::wheelDelta_ {};
bool Mouse::hasEntered_ {false};
bool Mouse::hasLeft_ {false};
bool Mouse::visible_ {true};
bool Mouse::locked_ {false};
std::array<bool, Mouse::Button::ButtonCount> Mouse::currentState_ {};
std::array<bool, Mouse::Button::ButtonCount> Mouse::lastState_ {};

tank::Vectord Mouse::getRelPos(Camera const& c)
{
    auto const& cPos = c.getPos();
    const auto cRot = c.getRotation();
    auto const& cOgn = c.getOrigin();
    auto const& cScale = c.getZoom();


    tank::Vectord pos = getPos() - cOgn;
    pos = pos.rotate(cRot);
    pos.x /= cScale.x;
    pos.y /= cScale.y;
    pos += cOgn;

    pos += cPos.rotate(cRot);

    return pos;

}

tank::Vectori Mouse::delta() { return currentPos_ - lastPos_; }

bool Mouse::isButtonPressed(Button button)
{
    return currentState_[button] and not lastState_[button];
}

std::function<bool()> Mouse::ButtonPress(Button button)
{
    return [button]
    {
        return isButtonPressed(button);
    };
}

bool Mouse::isButtonReleased(Button button)
{
    return lastState_[button] and not currentState_[button];
}

std::function<bool()> Mouse::ButtonRelease(Button button)
{
    return [button]
    {
        return isButtonReleased(button);
    };
}

bool Mouse::isButtonDown(Button button)
{
    return currentState_[button];
}

std::function<bool()> Mouse::ButtonDown(Button button)
{
    return [button]
    {
        return isButtonDown(button);
    };
}

bool Mouse::isButtonUp(Button button)
{
    return not currentState_[button];
}

std::function<bool()> Mouse::ButtonUp(Button button)
{
    return [button]
    {
        return isButtonUp(button);
    };
}

std::function<bool()> Mouse::MouseMovement()
{
    return []
    {
        auto dt = delta();
        return dt.x != 0 or dt.y != 0;
    };
}

std::function<bool()> Mouse::WheelUp()
{
    return []
    {
        return wheelDelta() > 0;
    };
}

std::function<bool()> Mouse::WheelDown()
{
    return []
    {
        return wheelDelta() < 0;
    };
}
std::function<bool()> Mouse::WheelMovement()
{
    return []
    {
        return wheelDelta() != 0;
    };
}

std::function<bool()> Mouse::InEntity(Entity const& e)
{
    return [&e]
    {
        auto mPos = getRelPos(e.getWorld()->camera());
        auto ePos = e.getPos();
        auto hb = e.getHitbox();
        hb.x += ePos.x;
        hb.w += ePos.x;
        hb.y += ePos.y;
        hb.h += ePos.y;

        return mPos.x > hb.x and mPos.x < hb.w and
               mPos.y > hb.y and mPos.y < hb.h;
    };
}


void Mouse::setButtonPressed(Button button)
{
    stateChange_ = true;
    currentState_[button] = true;
}

void Mouse::setButtonReleased(Button button)
{
    stateChange_ = true;
    currentState_[button] = false;
}

void Mouse::setPos(int x, int y)
{
    stateChange_ = true;
    currentPos_ = {x, y};
}

void Mouse::setWheelDelta(int dt)
{
    stateChange_ = true;
    wheelDelta_ = dt;
}

void Mouse::setLeft()
{
    stateChange_ = true;
    hasLeft_ = true;
}
void Mouse::setEntered()
{
    stateChange_ = true;
    hasEntered_ = true;
}

void Mouse::reset()
{
    if (not stateChange_) return;

    std::copy(currentState_.begin(), currentState_.end(), lastState_.begin());

    if (locked_)
    {
        sf::Mouse::setPosition({lockPos_.x, lockPos_.y}, Game::window()->SFMLWindow());
        currentPos_ = lockPos_;
    }

    lastPos_ = currentPos_;
    wheelDelta_ = 0;
    hasEntered_ = false;
    hasLeft_ = false;

    stateChange_ = false;
}

void Mouse::setVisibility(bool visible)
{
    Game::window()->SFMLWindow().setMouseCursorVisible(visible);
    visible_ = visible;
}

}
