#include "Game/GameObject.h"

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

CGameObject::CGameObject(CPlatformerGame* game)
{
   Game = game;
}

void CGameObject::onKey(int keyCode, KeyState keyState)
{
}