#include "raylib.h"
#include <random>
#include <float.h>

#include "PlatformerGame.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"
#include "Player.h"
#include "AABB.h"
#include "Block.h"


CPlatformerGame::CPlatformerGame()
{
    std::random_device rd;
    srand( rd() );

    Textures["SoccerBall"] = LoadTexture( "Data/Textures/SoccerBall.png" );

    // Creating the blocks
    m_Blocks.push_back(new CBlock(vec2(100, 500), vec2(1050, 50), DARKBLUE)); // Floor
    m_Blocks.push_back(new CBlock(vec2(100, 0), vec2(50, 500), DARKBLUE)); // Left Wall
    m_Blocks.push_back(new CBlock(vec2(1100, 0), vec2(50, 500), DARKBLUE)); // Left Wall
    
    
    Player = new CPlayer( this );

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
}

void CPlatformerGame::update(float deltaTime)
{
    Player->update( deltaTime );
}

void CPlatformerGame::draw()
{
    ClearBackground( WHITE );

    DrawCircle( 400, 300, 50, RED );
    DrawTexture( getTexture("SoccerBall"), 500, 300, WHITE );
    DrawText( "Hello", 600, 300, 50, DARKGRAY );

    Player->draw();

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
