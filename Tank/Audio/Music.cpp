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
    if (!loaded_) {
        throw std::runtime_error("Failed to load music file");
    }
    return loaded_;
}

void Music::play()
{
    if (loaded_) {
        music_->play();
    } else {
        Game::log << "Attempt to play empty music" << std::endl;
    }
}

void Music::pause()
{
    if (loaded_) {
        music_->pause();
    } else {
        Game::log << "Attempt to pause empty music" << std::endl;
    }
}

void Music::stop()
{
    if (loaded_) {
        music_->stop();
    } else {
        Game::log << "Attempt to stop empty music" << std::endl;
    }
}

void Music::setVolume(float v)
{
    if (loaded_) {
        music_->setVolume(v);
    } else {
        Game::log << "Attempt to set volume on empty music" << std::endl;
    }
}

float Music::getVolume()
{
    if (loaded_) {
        return music_->getVolume();
    } else {
        Game::log << "Attempt to get volume on empty music" << std::endl;
        // Return default value.
        return {};
    }
}

void Music::setLoop(bool loop)
{
    if (loaded_) {
        music_->setLoop(loop);
    } else {
        Game::log << "Attempt to set loop on empty music" << std::endl;
    }
}

bool Music::getLoop()
{
    if (loaded_) {
        return music_->getLoop();
    } else {
        Game::log << "Attempt to get loop on empty music" << std::endl;
        // Return default value.
        return {};
    }
}
}
