/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#ifndef TANK_SOUNDEFFECT_HPP
#define TANK_SOUNDEFFECT_HPP

#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace tank {

class SoundEffect
{
    sf::SoundBuffer buffer_;
    sf::Sound sound_;
    bool loaded_ = false;

public:
    SoundEffect(std::string fileName);

    bool load(std::string fileName);

    void play();

    explicit operator bool()
    {
        return loaded_;
    }

};

}

#endif //TANK_SOUNDEFFECT_HPP
