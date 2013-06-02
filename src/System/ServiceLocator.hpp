#pragma once
#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include "../Graphics/IRender.hpp"

class ServiceLocator
{
public:
    static IRender* getRender();
    static void provide(IRender*);
private:
    static IRender* _render;
    static NullRender _nullRender;
};
#endif
