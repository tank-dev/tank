#include "ServiceLocator.hpp"

IRender* ServiceLocator::_render;
NullRender ServiceLocator::_nullRender;

IRender* ServiceLocator::getRender()
{
    return _render;
}

void ServiceLocator::provide( IRender* r )
{
    if( r )
    {
        _render = r;
    }
    else
    {
        _render = &_nullRender;
    }
}
