#pragma once
#include "Helpers/Vector.h"


class AABB
{
public:
    
    AABB();
    AABB(vec2& position, vec2& size);
    
    bool isPointInside(vec2 point);

private:
    float x; // Position
    float y; // Position
    float w; // Width
    float h; // Height
};