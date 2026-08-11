#include "raylib.h"
#include <random>
#include <float.h>

#include "MenuState.h"
#include "PlatformerGame.h"

CMenuState::CMenuState(CPlatformerGame* game) : CGameState(game)
{
}

CMenuState::~CMenuState()
{
}

void CMenuState::update(float deltaTime)
{
}

void CMenuState::draw()
{
	ClearBackground(RAYWHITE);

	DrawText("Chaos Collector", 200, 200, 50, DARKPURPLE);
	DrawText("Press ENTER to play", 200, 150, 50, BLACK);
}

void CMenuState::onActivate()
{
}

void CMenuState::onDeactive()
{
}

void CMenuState::onKey(int keyCode, KeyState keyState)
{
	if (keyCode == KEY_ENTER && keyState == KeyState::Pressed)
	{
		Game->setState(GameStateType::Gameplay);
	}
}

void CMenuState::onMouseButton(int button, KeyState keyState)
{
}

void CMenuState::onMouseMove(int x, int y)
{
}
