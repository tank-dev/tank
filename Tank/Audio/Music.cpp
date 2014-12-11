// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Music.hpp"
#include "../System/Game.hpp"

namespace tank
{

Music::Music(std::string fileName)
{
    load(fileName);
}

bool Music::load(std::string fileName)
{
    if (loaded_) {
        Game::log << "Music already loaded!" << std::endl;
        return loaded_;
    }
    loaded_ = music_->openFromFile(fileName);
    return loaded_;
}

void Music::play()
{
    music_->play();
}

void Music::pause()
{
    music_->pause();
}

void Music::stop()
{
    music_->stop();
}
}
