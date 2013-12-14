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

#ifndef TANK_MOUSE_HPP
#define TANK_MOUSE_HPP

#include <array>
#include <functional>
#include <SFML/Window/Mouse.hpp>
#include "../../Tank/Utility/Vector.hpp"
#include "../../Tank/Utility/Rect.hpp"
#include "../../Tank/System/Camera.hpp"

namespace tank {

class Entity;
class Mouse {
    friend class Game;
    static bool stateChange_;
    static Vectori currentPos_;
    static Vectori lastPos_;
    static Vectori lockPos_;
    static int wheelDelta_;
    static bool hasEntered_;
    static bool hasLeft_;
    static bool visible_;
    static bool locked_;
    static std::array<bool, sf::Mouse::Button::ButtonCount> currentState_;
    static std::array<bool, sf::Mouse::Button::ButtonCount> lastState_;

public:
    using Button = sf::Mouse::Button;
    static tank::Vectori const& getPos() { return currentPos_; }
    static tank::Vectord getRelPos(Camera const&);
    static tank::Vectori delta();
    static int const& wheelDelta() { return wheelDelta_; }

    static bool isButtonPressed(Button button);
    static std::function<bool()> ButtonPress(Button button);

    static bool isButtonReleased(Button button);
    static std::function<bool()> ButtonRelease(Button button);

    static bool isButtonDown(Button button);
    static std::function<bool()> ButtonDown(Button button);

    static bool isButtonUp(Button button);
    static std::function<bool()> ButtonUp(Button button);

    static std::function<bool()> WheelUp();
    static std::function<bool()> WheelDown();
    static std::function<bool()> WheelMovement();

    static std::function<bool()> EnterWindow();
    static std::function<bool()> LeaveWindow();

    template <typename T>
    static bool isInRect(Rect<T> const& rect)
    {
        auto mPos = getPos();

        return rect.intersects(mPos);
    }

    template <typename T>
    static std::function<bool()> InRect(Rect<T> const& rect)
    {
        return [&rect]
        {
            return isInRect(rect);
        };

    }

    static std::function<bool()> InEntity(Entity const&);

    static std::function<bool()> MouseMovement();

    static bool isLocked() { return locked_; }
    static void setLock(bool lock) { locked_ = lock; }
    static void toggleLock() { setLock(!locked_); }
    static void setLockPosition(Vectorf pos) { lockPos_ = pos; }
    static Vectori const& getLockPosition() { return lockPos_; }

    static bool isVisible() { return visible_; }
    static void setVisibility(bool);
    static void toggleVisibility() { setVisibility(!visible_); }

private:
    static void setButtonPressed(Button);
    static void setButtonReleased(Button);
    static void setPos(int x, int y);
    static void setWheelDelta(int dt);
    static void setLeft();
    static void setEntered();

    static void reset();
};
}

#endif //TANK_MOUSE_HPP
