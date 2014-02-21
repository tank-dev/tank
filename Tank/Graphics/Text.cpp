// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Text.hpp"

namespace tank
{
void Text::draw(Vectorf parentPos, float parentRot, Camera const& cam)
{
    Graphic::transform(this, parentPos, parentRot, cam, text_);
    Game::window()->SFMLWindow().draw(text_);
}
}
