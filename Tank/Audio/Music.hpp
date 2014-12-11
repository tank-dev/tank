// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef TANK_MUSIC_HPP
#define TANK_MUSIC_HPP

#include <string>
#include <memory>
#include <SFML/Audio/Music.hpp>

namespace tank
{

class Music
{
    std::shared_ptr<sf::Music> music_ = std::make_shared<sf::Music>();
    bool loaded_ = false;

public:
    Music() = default;
    Music(std::string fileName);
    Music(Music const&) = default;
    Music& operator=(Music const&) = default;

    bool load(std::string fileName);
    bool loadFromFile(std::string fileName) {return load(fileName);}

    void play();
    void pause();
    void stop();

    void setVolume(float v) { music_->setVolume(v); }
    float getVolume() { return music_->getVolume(); }
    void setLoop(bool loop) { music_->setLoop(loop); }
    bool getLoop() { return music_->getLoop(); }

    explicit operator bool()
    {
        return loaded_;
    }
};
}

#endif // TANK_MUSIC_HPP
