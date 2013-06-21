#pragma once
#ifndef TANK_SERVICELOCATOR_HPP
#define TANK_SERVICELOCATOR_HPP

#include <memory>
#include "../Graphics/IRender.hpp"

class ServiceLocator
{
public:
    static IRender* getRender();
    static void provide(IRender*);
private:
    static IRender* render_;
    static NullRender nullRender_;
};
#endif
