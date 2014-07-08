// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_KEYBOARD_HPP
#define TANK_KEYBOARD_HPP
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <array>

namespace tank
{

using Key = sf::Keyboard::Key;

/*!
 * \brief Static class representing the state of the keyboard
 *
 * Updated by Game before calling EventHandler.propagate() and World.update().
 *
 * You can either check the state directly (*e.g.* Keyboard::isKeyDown()), or
 * register an event with an EventHandler:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
 * class MyEnt : public tank::Entity
 * {
 *     std::unique_ptr<tank::EventHandler::Connection> c;
 * public:
 *     // Must manage connections in onAdded, as getWorld() is not set at
 *     // construction
 *     virtual void onAdded() override
 *     {
 *         using Kbd = tank::Keyboard;
 *         using Key = tank::Key;
 *         c = getWorld().eventHandler.connect(Kbd::KeyDown(Key::Left), move);
 *     }
 *
 *     // is equivalent to...
 *     virtual void update() override
 *     {
 *         using Kbd = tank::Keyboard;
 *         using Key = tank::Key;
 *
 *         if (Kbd::isKeyDown(Key::Left) {
 *             move();
 *         }
 *     }
 * };
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * \see EventHandler
 */
class Keyboard
{
    friend class Game;
    static bool stateChange_;
    static std::array<bool, Key::KeyCount> currentState_;
    static std::array<bool, Key::KeyCount> lastState_;

public:
    /*! \brief Function returning whether the specified Key is currently down */
    static std::function<bool()> KeyDown(Key key)
    {
        return [key]() { return isKeyDown(key); };
    }

    /*! \brief Function returning whether the specified Key is currently up */
    static std::function<bool()> KeyUp(Key key)
    {
        return [key]() { return not isKeyDown(key); };
    }

    /*! \brief Function returning whether the specified Key has just been pressed */
    static std::function<bool()> KeyPress(Key key)
    {
        return [key]() { return isKeyPressed(key); };
    }

    /*! \brief Function returning whether the specified Key has just been released*/
    static std::function<bool()> KeyRelease(Key key)
    {
        return [key]() { return isKeyReleased(key); };
    }

    /*! \brief returns whether the specified Key is currently down */
    static bool isKeyDown(Key key)
    {
        return currentState_[key];
    }

    /*! \brief returns whether the specified Key is currently up */
    static bool isKeyUp(Key key)
    {
        return not isKeyDown(key);
    }

    /*! \brief returns whether the specified Key has just been pressed */
    static bool isKeyPressed(Key key)
    {
        return stateChange_ and currentState_[key] and not lastState_[key];
    }

    /*! \brief returns whether the specified Key has just been released */
    static bool isKeyReleased(Key key)
    {
        return stateChange_ and not currentState_[key] and lastState_[key];
    }

private:
    static void reset();

    static void setKeyPressed(Key key);
    static void setKeyReleased(Key key);
};
}

#endif /* TANK_KEYBOARD_HPP */
