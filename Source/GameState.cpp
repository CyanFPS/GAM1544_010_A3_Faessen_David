#include "raylib.h"
#include <random>
#include <float.h>

#include "GameState.h"

CGameState::CGameState(CPlatformerGame* game)
{
	Game = game;
}

CGameState::~CGameState()
{
}

void CGameState::update(float deltaTime)
{
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
