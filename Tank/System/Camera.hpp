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

#ifndef TANK_CAMERA_HPP
#define TANK_CAMERA_HPP

#include "../Utility/Vector.hpp"

namespace tank {

class Camera
{
    float rot_ {0};
    Vectorf pos_ {};
public:
    Vectorf getPos() const { return pos_; }
    void setPos(Vectorf pos) { pos_ = pos; }

    float getRotation() const { return rot_; }
    void setRotation(float rot) { rot_ = rot; }
private:
};

} /* tank */

#endif /* TANK_CA<ERA_HPP */
