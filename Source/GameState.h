#pragma once
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"

class CPlatformerGame;

class CGameState
{
public:
	CGameState(CPlatformerGame* game);
	virtual ~CGameState();

	virtual void update(float deltaTime);
	virtual void draw();

	virtual void onActivate();
	virtual void onDeactive();

	virtual void onKey(int keyCode, KeyState keyState);
	virtual void onMouseButton(int button, KeyState keyState);
	virtual void onMouseMove(int x, int y);

	bool isSliding();

protected:
	CPlatformerGame* Game;

	vec2 m_Offset;
	float m_SlideSpeed;
	bool m_isSliding;
};