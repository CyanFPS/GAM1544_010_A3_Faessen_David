#include "raylib.h"
#include <random>
#include <float.h>

#include "GameoverState.h"
#include "PlatformerGame.h"

CGameoverState::CGameoverState(CPlatformerGame* game) : CGameState(game)
{
}

CGameoverState::~CGameoverState()
{
}

void CGameoverState::update(float deltaTime)
{
}

void CGameoverState::draw()
{
    ClearBackground(WHITE);
    
    DrawText("GAME OVER", 500, 200, 50, RED);

    DrawText(TextFormat("Collected: %i", Game->CountCollectables()), 500, 250, 50, DARKBLUE);

    DrawText("Press ENTER to retry.", 525, 300, 20, BLACK);
}

void CGameoverState::onActivate()
{
}

void CGameoverState::onDeactive()
{
}

void CGameoverState::onKey(int keyCode, KeyState keyState)
{
    if (keyCode == KEY_ENTER && keyState == KeyState::Pressed)
    {
        Game->setState(GameStateType::Gameplay);
    }
}

void CGameoverState::onMouseButton(int button, KeyState keyState)
{
}

void CGameoverState::onMouseMove(int x, int y)
{
}