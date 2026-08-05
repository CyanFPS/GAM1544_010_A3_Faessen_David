#include "Collectable.h"

CCollectable::CCollectable(CPlatformerGame* game, vec2 position)
    : Game(game)
{
    m_Position = position;
    m_Radius = 10.0f;
    m_Collected = false;

    Sprite = new Sprite2D(Game->getTexture("Collectable"));
}

CCollectable::~CCollectable()
{
    delete Sprite;
}

void CCollectable::draw()
{
    if (!m_Collected)
    {
        Sprite->draw(m_Position, 0.0f, 0.05f, false);
    }
}

vec2 CCollectable::getPosition()
{
    return m_Position;
}

float CCollectable::getRadius()
{
    return m_Radius;
}

bool CCollectable::isCollected()
{
    return m_Collected;
}

void CCollectable::setCollected(bool collected)
{
    m_Collected = collected;
}

void CCollectable::respawn()
{
    m_Position.X = (float)(rand() % 1000 + 50);
    m_Position.Y = (float)(rand() % 500 + 50);

    m_Collected = false;
}

