#include "raylib.h"
#include <random>
#include <float.h>

#include "PlatformerGame.h"
#include "GameState.h"
#include "MenuState.h"
#include "GameplayState.h"
#include "GameoverState.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"


CPlatformerGame::CPlatformerGame()
{
    m_CollectedNum = 0;
    
    std::random_device rd;
    srand( rd() );

    Textures["SoccerBall"] = LoadTexture( "Data/Textures/SoccerBall.png" );
    Textures["Collectable"] = LoadTexture("Data/Textures/CollectableSprite.png");

    m_States.push_back(new CMenuState(this));
    m_States.push_back(new CGameplayState(this));
    m_States.push_back(new CGameoverState(this));

    m_CurrentState = GameStateType::Menu;
}

CPlatformerGame::~CPlatformerGame()
{
    for( auto texturePair : Textures )
    {
        UnloadTexture( texturePair.second );
    }
}


void CPlatformerGame::update(float deltaTime)
{
}

void CPlatformerGame::draw()
{
}

void CPlatformerGame::setState(GameStateType state)
{
}

void CPlatformerGame::onKey(int keyCode, KeyState keyState)
{
}

void CPlatformerGame::onMouseButton(int button, KeyState keyState)
{
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
