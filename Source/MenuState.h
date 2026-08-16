#pragma once
#include "GameState.h"
#include "Helpers/InputTypes.h"

class CMenuState : public CGameState
{
public:
	CMenuState(CPlatformerGame* game);
	~CMenuState();

	void update(float deltaTime);
	void draw();

	void onActivate();
	void onDeactive();

	// Input event methods.
	void onKey(int keyCode, KeyState keyState);
	void onMouseButton(int button, KeyState keyState);
	void onMouseMove(int x, int y);

private:
	bool m_DebugMode;
	bool m_Level2;
};