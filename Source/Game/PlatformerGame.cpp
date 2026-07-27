#include "raylib.h"
#include <random>
#include <float.h>

#include "PlatformerGame.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"


CPlatformerGame::CPlatformerGame()
{
    std::random_device rd;
    srand( rd() );

    Textures["SoccerBall"] = LoadTexture( "Data/Textures/SoccerBall.png" );
    
    Player = new CPlayer( this );

    Ball = new CBall( this );
    Ball->setVelocity({ 50,0 });

     m_Blocks.push_back(new CBlock(vec2(100, 500), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(300, 500), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(500, 500), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(700, 500), vec2(200, 50), DARKBLUE));
    
     reset();
}

CPlatformerGame::~CPlatformerGame()
{
    for( auto texturePair : Textures )
    {
        UnloadTexture( texturePair.second );
    }
}

void CPlatformerGame::reset()
{
    Player->setPosition({ 200,300 });
}

void CPlatformerGame::update(float deltaTime)
{
    Player->update( deltaTime );
    Ball->update(deltaTime);
}

void CPlatformerGame::draw()
{
    ClearBackground( WHITE );

    DrawCircle( 400, 300, 50, RED );
    DrawTexture( getTexture("SoccerBall"), 500, 300, WHITE );
    DrawText( "Hello", 600, 300, 50, DARKGRAY );

    Player->draw();
    Ball->draw();

    // Outputting the Debug Collision
    if (DebugVisualsEnabled)
    {
        Player->drawDebugVisuals();
    }
    
    // Outputting the Blocks
    for (CBlock* block : m_Blocks)
    {
        block->draw();
    }
}

std::vector<CBlock*>& CPlatformerGame::getBlocks()
{
    return m_Blocks;
}

void CPlatformerGame::onKey(int keyCode, KeyState keyState)
{
    if( keyCode == 'R' && keyState == KeyState::Pressed )
    {
        reset();
    }
    if (keyCode == KEY_TAB && keyState == KeyState::Pressed)
    {
        DebugVisualsEnabled = !DebugVisualsEnabled;
    }

    Player->onKey(keyCode, keyState); // Calling onKey to make the player move.
}

void CPlatformerGame::onMouseButton(int button, KeyState keyState)
{
}

void CPlatformerGame::onMouseMove(int x, int y)
{
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

CBall* CPlatformerGame::getBall()
{
    return Ball;
}
