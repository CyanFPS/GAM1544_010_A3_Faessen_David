#pragma once
#include "Helpers/Vector.h"

class AABB
{
public:
    bool isPointInside(vec2 point);

private:
    float x; // Position
    float y; // Position
    float w; // Width
    float h; // Height
};