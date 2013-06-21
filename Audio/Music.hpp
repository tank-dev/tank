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
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson
 */

#ifndef TANK_MUSIC_HPP
#define TANK_MUSIC_HPP

#include <string>
#include <SFML/Audio/Music.hpp>

namespace tank {

class Music {
    sf::Music music_;
    bool loaded_ = false;

public:
    Music(std::string fileName);

    bool load(std::string fileName);

    void play();
    void pause();
    void stop();

    explicit operator bool()
    {
        return loaded_;
    }
};

}

#endif //TANK_MUSIC_HPP
