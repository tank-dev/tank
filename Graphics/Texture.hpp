#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

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
#endif
