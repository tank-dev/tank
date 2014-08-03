// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Text.hpp"

#include "../System/Game.hpp"

namespace tank
{
void Text::draw(Transform const& parent, Camera const& cam)
{
    Graphic::transform(this, parent.position, parent.rotation, parent.origin,
                       cam, text_);
    Game::window()->SFMLWindow().draw(text_);
}
}
