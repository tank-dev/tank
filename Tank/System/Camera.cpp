// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Camera.hpp"

#include "Game.hpp"

namespace tank
{

Camera::Camera()
{
    if (Game::window())
    {
        setOrigin(Game::window()->getSize() / 2);
        setPos(Game::window()->getSize() / 2);
    }
}

} /* tank */
