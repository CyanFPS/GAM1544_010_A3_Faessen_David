#include "raylib.h"
#include <random>
#include <float.h>

#include "GameState.h"

CGameState::CGameState(CPlatformerGame* game) : Game(game)
{
    Game = game;

    m_Offset.X = -1280;
    m_Offset.Y = 0;

    m_isSliding = true;

    m_SlideTimer = 0.0f;
    m_SlideDuration = 0.5f;
    m_StartOffsetX = -1280.0f;
}

CGameState::~CGameState()
{
}

void CGameState::update(float deltaTime)
{
    if (m_isSliding)
    {
        m_SlideTimer += deltaTime;

        float t = m_SlideTimer / m_SlideDuration;

        if (t >= 1.0f)
        {
            t = 1.0f;
            m_isSliding = false;
        }

        float eased = Quadratic::InOut(t);

        m_Offset.X = m_StartOffsetX * (1.0f - eased);
    }
}

void CGameState::draw()
{
}

void CGameState::onActivate()
{
    m_isSliding = true;
    m_SlideTimer = 0.0f;
    m_Offset.X = m_StartOffsetX;
}

void CGameState::onDeactive()
{
}

void CGameState::onKey(int keyCode, KeyState keyState)
{
}

void CGameState::onMouseButton(int button, KeyState keyState)
{
}

void CGameState::onMouseMove(int x, int y)
{
}

bool CGameState::isSliding()
{
    return m_isSliding;
}
