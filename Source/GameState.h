#pragma once

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

protected:
	CPlatformerGame* Game;
};