#include "AABB.h"

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

