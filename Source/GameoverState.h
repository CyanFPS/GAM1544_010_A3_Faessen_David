#pragma once
#include "GameState.h"
#include "Helpers/InputTypes.h"

class CGameoverState : public CGameState
{
public:
	CGameoverState(CPlatformerGame* game);
	~CGameoverState();

	void update(float deltaTime);
	void draw();

	void onActivate();
	void onDeactive();

	// Input event methods.
	void onKey(int keyCode, KeyState keyState);
	void onMouseButton(int button, KeyState keyState);
	void onMouseMove(int x, int y);
};