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

#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace tank {

struct Texture
{
public:
    std::string name; /* Name to identify texture */
    int width, height;

    /*------------------------- *
     * Constructors
     * ------------------------ */
    /*Texture()
    :name( "null" ), width( 0 ), height( 0 ) {}
    Texture( int w, int h, std::string const& name )
    :name( name ), width( w ), height( h ) {}*/

    //const int id;      /* Ties texture to platform-dependent image structure */
};
}
#endif
