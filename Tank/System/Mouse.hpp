// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_MOUSE_HPP
#define TANK_MOUSE_HPP

#include <array>
#include <functional>
#include <SFML/Window/Mouse.hpp>
#include "../../Tank/Utility/Vector.hpp"
#include "../../Tank/Utility/Rect.hpp"
#include "../../Tank/System/Camera.hpp"

namespace tank
{

class Entity;
class Mouse
{
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
    static tank::Vectori const& getPos()
    {
        return currentPos_;
    }
    static tank::Vectord getRelPos(Camera const&);
    static tank::Vectori delta();
    static int const& wheelDelta()
    {
        return wheelDelta_;
    }

    static bool isButtonPressed();
    static bool isButtonPressed(Button button);
    static std::function<bool()> ButtonPress();
    static std::function<bool()> ButtonPress(Button button);

    static bool isButtonReleased();
    static bool isButtonReleased(Button button);
    static std::function<bool()> ButtonRelease();
    static std::function<bool()> ButtonRelease(Button button);

    static bool isButtonDown();
    static bool isButtonDown(Button button);
    static std::function<bool()> ButtonDown();
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
        return [&rect] { return isInRect(rect); };
    }

    static std::function<bool()> InEntity(Entity const&);
    static bool isInEntity(Entity const&);

    static std::function<bool()> MouseMovement();

    static bool isLocked()
    {
        return locked_;
    }
    static void setLock(bool lock)
    {
        locked_ = lock;
    }
    static void toggleLock()
    {
        setLock(!locked_);
    }
    static void setLockPosition(Vectorf pos)
    {
        lockPos_ = pos;
    }
    static Vectori const& getLockPosition()
    {
        return lockPos_;
    }

    static bool isVisible()
    {
        return visible_;
    }
    static void setVisibility(bool);
    static void toggleVisibility()
    {
        setVisibility(!visible_);
    }

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

#endif // TANK_MOUSE_HPP
