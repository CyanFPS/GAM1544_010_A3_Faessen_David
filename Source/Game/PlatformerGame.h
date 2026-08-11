#pragma once

#include <assert.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "raylib.h"
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"


class CGameState;
class CMenuState;
class CGameplayState;
class CGameoverState;

enum class GameStateType
{
    Menu,
    Gameplay,
    Gameover
};

class CPlatformerGame
{
public:
    CPlatformerGame();
    virtual ~CPlatformerGame();

    void update(float deltaTime);
    void draw();

    // State Management
    void setState(GameStateType state);
    
    // Input event methods.
    void onKey(int keyCode, KeyState keyState);
    void onMouseButton(int button, KeyState keyState);
    void onMouseMove(int x, int y);
    
    // Collectable Data
    void AddCollectedCount();
    int CountCollectables();

    // Getters.
    Texture2D getTexture(const char* textureName) const;

private:
    std::unordered_map<std::string, Texture2D> Textures;

    std::vector<CGameState*> m_States;

    GameStateType m_CurrentState;
    
    // Collectable Counter
    int m_CollectedNum;
};
