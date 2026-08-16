#include "raylib.h"
#include <random>
#include <float.h>

#include "GameState.h"

CGameState::CGameState(CPlatformerGame* game) : Game(game)
{
    Game = game;

    m_Offset.X = -1280;
    m_Offset.Y = 0;

    m_SlideSpeed = 2000.0f;
    m_isSliding = true;
}

CGameState::~CGameState()
{
}

void CGameState::update(float deltaTime)
{
    if (m_isSliding)
    {
        m_Offset.X += m_SlideSpeed * deltaTime;
        
        if (m_Offset.X >= 0)
        {
            m_Offset.X = 0;
            m_isSliding = false;
        }
    }
}

void CGameState::draw()
{
}

void CGameState::onActivate()
{
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
