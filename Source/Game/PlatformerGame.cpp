#include "raylib.h"
#include <random>
#include <float.h>

#include "PlatformerGame.h"
#include "..//GameState.h"
#include "..//MenuState.h"
#include "..//GameplayState.h"
#include "..//GameoverState.h"
#include "..//Helpers/MathFuncs.h"
#include "..//Helpers/Sprite2D.h"


CPlatformerGame::CPlatformerGame()
{
    m_CollectedNum = 0;

    m_DebugMode = false;
    m_Level2 = false;
    
    std::random_device rd;
    srand( rd() );

    Textures["Background"] = LoadTexture("Data/Textures/GreenHillBackground.png");
    Textures["SoccerBall"] = LoadTexture( "Data/Textures/SoccerBall.png" );
    Textures["Collectable"] = LoadTexture("Data/Textures/CollectableSprite.png");

    m_States.push_back(new CMenuState(this));
    m_States.push_back(new CGameplayState(this));
    m_States.push_back(new CGameoverState(this));

    m_CurrentState = GameStateType::Menu;
}

CPlatformerGame::~CPlatformerGame()
{
    for (CGameState* state : m_States)
    {
        delete state;
    }
    
    
    for( auto texturePair : Textures )
    {
        UnloadTexture( texturePair.second );
    }
}


void CPlatformerGame::update(float deltaTime)
{
    int stateIndex = static_cast<int>(m_CurrentState);

    m_States[stateIndex]->update(deltaTime);
}

void CPlatformerGame::draw()
{
    int stateIndex = static_cast<int>(m_CurrentState);

    m_States[stateIndex]->draw();
}

void CPlatformerGame::setState(GameStateType state)
{
    int oldState = static_cast<int>(m_CurrentState);

    m_States[oldState]->onDeactive();
    
    m_CurrentState = state;

    int stateIndex = static_cast<int>(m_CurrentState);

    m_States[stateIndex]->onActivate();
}

void CPlatformerGame::onKey(int keyCode, KeyState keyState)
{
    int stateIndex = static_cast<int>(m_CurrentState);

    m_States[stateIndex]->onKey(keyCode, keyState);
}

void CPlatformerGame::onMouseButton(int button, KeyState keyState)
{
    int stateIndex = static_cast<int>(m_CurrentState);

    m_States[stateIndex]->onMouseButton(button, keyState);
}

void CPlatformerGame::onMouseMove(int x, int y)
{
}

void CPlatformerGame::AddCollectedCount()
{
    m_CollectedNum++;
}

int CPlatformerGame::CountCollectables()
{
    return m_CollectedNum;
}

void CPlatformerGame::ResetCollectable()
{
    m_CollectedNum = 0;
}

void CPlatformerGame::setDebugMode(bool debugMode)
{
    m_DebugMode = debugMode;
}

void CPlatformerGame::setLevel2(bool level2)
{
    m_Level2 = level2;
}

Texture2D CPlatformerGame::getTexture(const char* textureName) const
{
    auto it = Textures.find( textureName );
    if( it != Textures.end() )
    {
        return it->second;
    }

    // Return an empty texture if not found.
    assert( false );
    return Texture2D();
}

bool CPlatformerGame::getDebugMode()
{
    return m_DebugMode;
}

bool CPlatformerGame::getLevel2()
{
    return m_Level2;
}
