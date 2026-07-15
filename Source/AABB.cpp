#include "AABB.h"

AABB::AABB()  
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

AABB::AABB(vec2& position, vec2& size)
{
        x = position.X,
        y = position.Y,
        w = size.X,
        h = size.Y;
}

bool AABB::isPointInside(vec2 point)
{
    if (point.X < x || point.X > x + w)
    {
        return false;
    }
    if (point.Y < y || point.Y > y + h)
    {
        return false;
    }
    return true;
}

