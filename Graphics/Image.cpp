#include "Image.hpp"

Image::Image()
    : loaded_(false)
{ }
Image::Image(std::string file)
    : Image()
{
    load(file);
} 

void Image::load(std::string file)
{
    if(not loaded_)
    {
        texture_.reset(new GLTexture(file));
    }
}

void Image::draw(Vectorf const& pos)
{
}
