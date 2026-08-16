#include "raylib.h"
#include <random>
#include <float.h>

#include "MenuState.h"
#include "PlatformerGame.h"

CMenuState::CMenuState(CPlatformerGame* game) : CGameState(game)
{
	m_DebugMode = false;
	m_Level2 = false;
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

	DrawText("Chaos Collector", 200, 150, 50, DARKPURPLE);
	DrawText("Press ENTER to play", 200, 200, 50, BLACK);

	// Options
	DrawText("OPTIONS", 200, 500, 40, BLACK);
	DrawText(TextFormat("TAB - Debug Visuals: %s", m_DebugMode ? "ON" : "OFF"), 200, 550, 25, BLACK);
	DrawText(TextFormat("LSHIFT - Hard Mode?: %s", m_Level2 ? "YES" : "NO"), 200, 600, 25, BLACK);

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
		Game->setDebugMode(m_DebugMode);
		Game->setLevel2(m_Level2);
		Game->setState(GameStateType::Gameplay);
	}

	if (keyCode == KEY_TAB && keyState == KeyState::Pressed)
	{
		m_DebugMode = !m_DebugMode;
	}
	
	if (keyCode == KEY_LEFT_SHIFT && keyState == KeyState::Pressed)
	{
		m_Level2 = !m_Level2;
	}
}

void CMenuState::onMouseButton(int button, KeyState keyState)
{
}

void CMenuState::onMouseMove(int x, int y)
{
}
