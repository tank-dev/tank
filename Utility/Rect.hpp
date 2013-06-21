#pragma once
#ifndef TANK_RECT_HPP
#define TANK_RECT_HPP

namespace tank {

/*!
 * \brief A rectangle stuct. Stored as ints. Top left x,y then width and height.
 */
struct Rect
{
    int x, y, w, h;
};

}

#endif
