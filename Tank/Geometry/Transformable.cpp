#include "Transformable.hpp"

namespace tank {

Transformable(Transformable&& t)
    : transform_(t.transform_)
{
    t.transform_ = Transform();
}
}
