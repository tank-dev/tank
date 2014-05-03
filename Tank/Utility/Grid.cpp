#include "Grid.hpp"

namespace tank 
{

template<typename T>
Grid<T>::Grid(const Vectoru& dims)
    : data(dims.x * dims.y)
    , dimensions(dims)
{}

template<typename T>
Grid<T>::Grid(const Vectoru& dims, T intialValue) 
    : data(dims.x * dims.y, intialValue)
    , dimensions(dims)
{}

template<typename T>
T& Grid<T>::operator[](const Vectoru& location)
{
    return data[dimensions.x * location.y + location.x];
}
template<typename T>
const T& Grid<T>::operator[](const Vectoru& location) const
{
    return data[dimensions.x * location.y + location.x];
}

template<typename T>
T& Grid<T>::at(const Vectoru& location)
{
    if (location.x < dimensions.x and location.y < dimensions.y)
    {
        return data[dimensions.x * location.y + location.x];
    }
    else
    {
        throw std::out_of_range("Invalid Argument");
    }
}
template<typename T>
const T& Grid<T>::at(const Vectoru& location) const
{
    if (location.x < dimensions.x and location.y < dimensions.y)
    {
        return data[dimensions.x * location.y + location.x];
    }
    else
    {
        throw std::out_of_range("Invalid Argument");
    }
}

} // tank
