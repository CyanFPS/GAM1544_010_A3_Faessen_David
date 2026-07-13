#pragma once
#include "Helpers/Vector.h"

class AABB
{
public:
    bool isPointInside(vec2 point);

private:
    float x;
    float y;
    float w;
    float h;
};