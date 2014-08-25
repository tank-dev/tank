// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_SOUNDEFFECT_HPP
#define TANK_SOUNDEFFECT_HPP

#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace tank
{

class SoundEffect
{
    sf::SoundBuffer buffer_;
    sf::Sound sound_;
    bool loaded_ = false;

public:
    using Status = sf::Sound::Status;
    SoundEffect(std::string fileName);

    bool load(std::string fileName);
    bool loadFromFile(std::string fileName){return load(fileName);}

    void play();

    explicit operator bool()
    {
        return loaded_;
    }

    Status getStatus()
    {
        return sound_.getStatus();
    }
};
}

#endif // TANK_SOUNDEFFECT_HPP
