#pragma once

#include <assert.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"

class CPlayer;
class CBlock;
class CBall;
class CCollectable;

class CPlatformerGame
{
public:
    CPlatformerGame();
    virtual ~CPlatformerGame();

    void reset();
    void update(float deltaTime);
    void draw();
    
    // Method that asks for the Blocks
    std::vector<CBlock*>& getBlocks();

    // Method that asks for the Bouncing Balls
    std::vector<CBall*>& getBalls();

    // Methods for spawning and getting Collectables
    std::vector<CCollectable*>& getCollectables();
    void spawnCollectables();
    void AddCollectedCount();
    int CountCollectables();


    // Input event methods.
    void onKey(int keyCode, KeyState keyState);
    void onMouseButton(int button, KeyState keyState);
    void onMouseMove(int x, int y);

    // Getters.
    Texture2D getTexture(const char* textureName) const;
    CBall* getBall();

private:
    std::unordered_map<std::string, Texture2D> Textures;

    bool DebugVisualsEnabled = false;

    // Vector of CBlock Pointers
    std::vector<CBlock*> m_Blocks;
    std::vector<CBall*> m_Balls;
    
    std::vector<CCollectable*> m_Collectables;
    std::vector<vec2> m_CollectableSpawnPoints;

    float m_CollectableSpawnTimer = 0.0f;
    float m_CollectableSpawnInterval = 3.0f;
    int m_CollectedNum;
    
    CPlayer* Player;
    CBall* Ball;
};
