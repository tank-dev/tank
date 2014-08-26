// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "SoundEffect.hpp"
#include "../System/Game.hpp"

namespace tank
{

SoundEffect::SoundEffect(std::string fileName)
{
    load(fileName);
}

bool SoundEffect::load(std::string fileName)
{
    if (loaded_) {
        Game::log << "SoundEffect already loaded!" << std::endl;
        return loaded_;
    }
    loaded_ = buffer_->loadFromFile(fileName);
    sound_.setBuffer(*buffer_);
    return loaded_;
}

Vectorf SoundEffect::getPosition()
{ 
    auto pos = sound_.getPosition();
    return {pos.x, pos.y};
}
}
