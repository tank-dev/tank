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

#include "Music.hpp"
#include "../System/Game.hpp"

namespace tank {

Music::Music (std::string fileName)
{
    load(fileName);
}

bool Music::load (std::string fileName)
{
    if (loaded_) {
        Game::log << "Music already loaded!" << std::endl;
        return loaded_;
    }
    loaded_ = music_.openFromFile(fileName);
    return loaded_;
}

void Music::play()
{
    music_.play();
}

void Music::pause()
{
    music_.pause();
}

void Music::stop()
{
    music_.stop();
}

}
