#pragma once
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"
#include "Helpers/Easing.h"

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
	bool m_isSliding;

	// Easing Variables
	float m_SlideTimer;
	float m_SlideDuration;
	float m_StartOffsetX;
};