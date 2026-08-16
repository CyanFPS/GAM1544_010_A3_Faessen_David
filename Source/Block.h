#pragma once
#include "Helpers/Vector.h"
#include "Helpers/InputTypes.h"
#include "AABB.h"

class CBlock
{
public:
    CBlock(vec2& position, vec2& size, Color& color);

    void draw(vec2 offset);
    void drawDebugVisuals();

    // Getters
    vec2 getPosition();
    vec2 getSize();
    AABB& getAABB(); // Getting a vec2 from the AABB class

private:
    // Member Variables
    vec2 m_Position;
    vec2 m_Size;
    Color m_Colour;

    // Holding AABB as a member
    AABB m_AABB;
};

