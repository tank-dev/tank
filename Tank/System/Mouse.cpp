/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#include "Mouse.hpp"
#include "../System/Entity.hpp"

namespace tank {

bool Mouse::stateChange_ {false};
Vectori Mouse::currentPos_;
Vectori Mouse::lastPos_;
int Mouse::wheelDelta_ {};
bool Mouse::hasEntered_ {false};
bool Mouse::hasLeft_ {false};
std::array<bool, Mouse::Button::ButtonCount> Mouse::currentState_ {};
std::array<bool, Mouse::Button::ButtonCount> Mouse::lastState_ {};

tank::Vectori Mouse::getRelPos(Camera const& c)
{
    return currentPos_ + c.getPos();
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

// TODO: Could neaten this up, draws attention to some obvious helper functions
std::function<bool()> Mouse::IsInEntity(Entity const& e)
{
    return [&e]
    {
        auto mPos = getRelPos(e.getState()->camera());
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
    lastPos_ = currentPos_;
    wheelDelta_ = 0;
    hasEntered_ = false;
    hasLeft_ = false;

    stateChange_ = false;
}

}
