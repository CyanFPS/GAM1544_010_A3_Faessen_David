#pragma once
#include "Helpers/Vector.h"
#include "Helpers/InputTypes.h"
#include "AABB.h"

class CBlock
{
public:
    CBlock(vec2& position, vec2& size, Color& color);

    void draw();
    void drawDebugVisuals();

private:
    // Member Variables
    vec2 m_Position;
    vec2 m_Size;
    Color m_Colour;

    // Holding AABB as a member
    AABB m_AABB;
};

