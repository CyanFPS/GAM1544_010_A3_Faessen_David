#include "Block.h"


CBlock::CBlock(vec2& position, vec2& size, Color& color) : 
    m_Position(position),
    m_Size(size),
    m_Colour(color),
    m_AABB(position, size)
{
}

void CBlock::draw(vec2 offset)
{
    DrawRectangle(
        m_Position.X + offset.X, m_Position.Y + offset.Y,
        m_Size.X, m_Size.Y,
        m_Colour);
}

void CBlock::drawDebugVisuals()
{
    DrawRectangleLines(
        m_Position.X, m_Position.Y, 
        m_Size.X, m_Size.Y, 
        { 255, 109, 194, 200 });
}

vec2 CBlock::getPosition()
{
    return m_Position;
}

vec2 CBlock::getSize()
{
    return m_Size;
}

AABB& CBlock::getAABB()
{
    return m_AABB;
}














