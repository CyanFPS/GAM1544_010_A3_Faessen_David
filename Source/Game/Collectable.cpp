#include "Collectable.h"

CCollectable::CCollectable(CPlatformerGame* game, vec2 position)
    : Game(game)
{
    m_Position = position;
    m_OriginalPosition = position;
    m_Radius = 10.0f;
    m_Collected = false;

    Sprite = new Sprite2D(Game->getTexture("Collectable"));

    m_AnimationTimer = 0.0f;
    m_AnimationDuration = 0.3f;
}

CCollectable::~CCollectable()
{
    delete Sprite;
}

void CCollectable::draw(vec2 offset)
{
    if (m_Radius <= 0.0f)
    {
        return;
    }
    
    Sprite->draw(m_Position + offset, 0.0f, 0.05f, false);
  
}

void CCollectable::update(float deltaTime)
{
    if (m_Collected)
    {
        m_AnimationTimer += deltaTime;

        float t = m_AnimationTimer / m_AnimationDuration;

        if (t >= 1.0f)
        {
            t = 1.0f;
        }

        float eased = Quadratic::InOut(t);

        m_Position.Y = m_OriginalPosition.Y - 40.0F * eased;

        m_Radius = 10.0f * (1.0f - eased);
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

