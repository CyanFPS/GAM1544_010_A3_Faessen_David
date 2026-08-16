#pragma once
#include "GameState.h"
#include <vector>
#include "raylib.h"
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"

class CPlayer;
class CBlock;
class CBall;
class CCollectable;

class CGameplayState : public CGameState
{
public: 
	CGameplayState(CPlatformerGame* game); 
	~CGameplayState();

	void update(float deltaTime);
    void draw();
	void reset();

	// State Events
	void onActivate();
	void onDeactive();
	void createLevel();
	void createLevel2();

	// Gameplay Objects
	std::vector<CBlock*>& getBlocks();
	std::vector<CBall*>& getBalls();
	std::vector<CCollectable*>& getCollectables();

	// Collectable Spawning
	void spawnCollectables();

	// Input event methods.
	void onKey(int keyCode, KeyState keyState);
	void onMouseButton(int button, KeyState keyState);
	void onMouseMove(int x, int y);

private:
	// Gameplay Objects
	std::vector<CBlock*> m_Blocks;
	std::vector<CBall*> m_Balls;
	std::vector<CCollectable*> m_Collectables;
	std::vector<vec2> m_CollectableSpawnPoints;

	// Collectable Spawning Timers
	float m_CollectableSpawnTimer;
	float m_CollectableSpawnInterval;

	// Timer for the game so it can end
	float m_GameplayTimer;

	// Player
	CPlayer* Player;
};