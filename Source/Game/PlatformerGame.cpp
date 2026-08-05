#include "raylib.h"
#include <random>
#include <float.h>

#include "PlatformerGame.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"
#include "Collectable.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"


CPlatformerGame::CPlatformerGame()
{
    m_CollectedNum = 0;
    
    std::random_device rd;
    srand( rd() );

    Textures["SoccerBall"] = LoadTexture( "Data/Textures/SoccerBall.png" );
    Textures["Collectable"] = LoadTexture("Data/Textures/CollectableSprite.png");
    
    Player = new CPlayer(this);

    Ball = new CBall( this );
    Ball->setVelocity({ 50,0 });

     // Floor
     m_Blocks.push_back(new CBlock(vec2(0, 700), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(100, 700), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(300, 700), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(500, 700), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(700, 700), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(900, 700), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(1000, 700), vec2(200, 50), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(1200, 700), vec2(200, 50), DARKBLUE));
     
     // Extra Platforms
     m_Blocks.push_back(new CBlock(vec2(250, 400), vec2(150, 25), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(450, 300), vec2(150, 25), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(650, 100), vec2(150, 25), DARKBLUE));
     m_Blocks.push_back(new CBlock(vec2(1000, 250), vec2(150, 25), DARKBLUE));

     // Collectables
     m_Collectables.push_back(new CCollectable(this, { 200.0f, 350.0f }));
     m_Collectables.push_back(new CCollectable(this, { 250.0f, 100.0f }));
     m_Collectables.push_back(new CCollectable(this, { 550.0f, 220.0f }));
     m_Collectables.push_back(new CCollectable(this, { 445.0f, 175.0f }));
     m_Collectables.push_back(new CCollectable(this, { 756.0f, 125.0f }));

     reset();
}

CPlatformerGame::~CPlatformerGame()
{
    for( auto texturePair : Textures )
    {
        UnloadTexture( texturePair.second );
    }

    for (CBall* ball : m_Balls)
    {
        delete ball;
    }
}

void CPlatformerGame::reset()
{
    Player->setPosition({ 200,300 });
}

void CPlatformerGame::update(float deltaTime)
{
    Player->update(deltaTime);


    m_CollectableSpawnTimer += deltaTime;

    if (m_CollectableSpawnTimer >= m_CollectableSpawnInterval)
    {
        m_CollectableSpawnTimer = 0.0f;

        if (m_Collectables.size() < 15)
        {
            spawnCollectables();
        }
    }

    for (auto it = m_Balls.begin(); it != m_Balls.end(); )
    {
        CBall* ball = *it;

        ball->update(deltaTime);
        if (!ball->isActive())
        {
            delete ball;
            it = m_Balls.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void CPlatformerGame::draw()
{
    ClearBackground( WHITE );

    DrawText( "Press 'TAB' for Debug", 600, 300, 50, DARKGRAY );
    DrawText(TextFormat("Collected: %i", m_CollectedNum), 600, 600, 50, DARKBLUE);

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

    // Outputting the shooting balls
    for (CBall* ball : m_Balls)
    {
        ball->draw();
    }
    
    // Outputting the collectables
    for (CCollectable* collectable : m_Collectables)
    {
        collectable->draw();
    }
}

std::vector<CBlock*>& CPlatformerGame::getBlocks()
{
    return m_Blocks;
}

std::vector<CBall*>& CPlatformerGame::getBalls()
{
    return m_Balls;
}

std::vector<CCollectable*>& CPlatformerGame::getCollectables()
{
    return m_Collectables;
}

void CPlatformerGame::spawnCollectables()
{
    if (m_CollectableSpawnPoints.empty())
    {
        return;
    }
    
    int randomIndex = GetRandomValue(0, (int)m_CollectableSpawnPoints.size() - 1);

    vec2 position = m_CollectableSpawnPoints[randomIndex];

    CCollectable* collectable = new CCollectable(this, position);

    m_Collectables.push_back(collectable);
}

void CPlatformerGame::AddCollectedCount()
{
    m_CollectedNum++;
}

int CPlatformerGame::CountCollectables()
{
    return m_CollectedNum;
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
    if (button == MOUSE_BUTTON_LEFT && keyState == KeyState::Pressed)
    {
        vec2 mousePosition = { (float) GetMouseX(), (float) GetMouseY() }; // Setting a mouse position so the ball fires in the direction of the mouse

        vec2 direction = mousePosition - Player->getPosition();
        direction.normalize();

        if (m_Balls.size() < 10) // If statement so no more than 10 balls appear on screen at once.
        {
            CBall* newBalls = new CBall(this);

            newBalls->setPosition(Player->getPosition());
            newBalls->setVelocity(direction * 600.0f);
            m_Balls.push_back(newBalls);
        }
    }
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
