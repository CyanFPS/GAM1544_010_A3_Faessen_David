#include "GameplayState.h"
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

CGameplayState::CGameplayState(CPlatformerGame* game) : CGameState(game)
{
    Player = new CPlayer(game);
    
    m_GameplayTimer = 30.0f;

	m_CollectableSpawnTimer = 0.0f;
	m_CollectableSpawnInterval = 3.0f;
}

CGameplayState::~CGameplayState()
{
    delete Player;
    
    for (CBall* ball : m_Balls)
    {
        delete ball;
    }
    m_Balls.clear();

    for (CBlock* block : m_Blocks)
    {
        delete block;
    }
    m_Blocks.clear();

    for (CCollectable* collectable : m_Collectables)
    {
        delete collectable;
    }
    m_Collectables.clear();
}

void CGameplayState::update(float deltaTime)
{
    CGameState::update(deltaTime);
    
    // Player Updates
    if (Player != nullptr)
    {
        Player->update(deltaTime);

        Player->blockCollision(m_Blocks);
        Player->ballCollision(m_Balls);
        Player->collectableCollision(m_Collectables);
    }

    // Collectable Easing Animations
    for (CCollectable* collectable : m_Collectables)
    {
        collectable->update(deltaTime);
    }

    m_GameplayTimer -= deltaTime;

    if (m_GameplayTimer <= 0.0f)
    {
        Game->setState(GameStateType::Gameover);
    }
    
    // Collectable Spawns
    m_CollectableSpawnTimer += deltaTime;

    if (m_CollectableSpawnTimer >= m_CollectableSpawnInterval)
    {
        m_CollectableSpawnTimer = 0.0f;

        if (m_Collectables.size() < 15)
        {
            spawnCollectables();
        }
    }

    // Ball Updates
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

void CGameplayState::draw()
{
    ClearBackground(WHITE);
    DrawTexture(Game->getTexture("Background"), 0, 0, WHITE);
    DrawText(TextFormat("Collected: %i", Game->CountCollectables()), 900, 600, 50, DARKBLUE);

    if (Player != nullptr)
    {
        Player->draw(m_Offset);
    }
    // Drawing Debug Visuals
    if (Game->getDebugMode())
    {
        Player->drawDebugVisuals(m_Offset);
    }

    // Outputting the Blocks
    for (CBlock* block : m_Blocks)
    {
        block->draw(m_Offset);
    }

    // Outputting the shooting balls
    for (CBall* ball : m_Balls)
    {
        ball->draw(m_Offset);
    }

    // Outputting the collectables
    for (CCollectable* collectable : m_Collectables)
    {
        collectable->draw(m_Offset);
    }
}

void CGameplayState::reset()
{
    m_GameplayTimer = 30.0f;

    for (CBlock* block : m_Blocks)
    {
        delete block;
    }
    m_Blocks.clear();

    for (CCollectable* collectable : m_Collectables)
    {
        delete collectable;
    }
    m_Collectables.clear();

    m_CollectableSpawnPoints.clear();

    m_CollectableSpawnTimer = 0.0f;

    Game->ResetCollectable();

    if (Player != nullptr)
    {
        delete Player;
    }
    
    Player = new CPlayer(Game);

    if (Game->getLevel2())
    {
        createLevel2();
    }
    else
    {
        createLevel();
    }
}

void CGameplayState::onActivate()
{
    reset();
}

void CGameplayState::onDeactive()
{
}

void CGameplayState::createLevel()
{
    
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
    m_Blocks.push_back(new CBlock(vec2(650, 550), vec2(150, 25), DARKBLUE));
    m_Blocks.push_back(new CBlock(vec2(750, 350), vec2(150, 25), DARKBLUE));
    m_Blocks.push_back(new CBlock(vec2(500, 200), vec2(150, 25), DARKBLUE));

    m_CollectableSpawnPoints.push_back(vec2(875.0f, 650.0f));
    m_CollectableSpawnPoints.push_back(vec2(300.0f, 375.0f));
    m_CollectableSpawnPoints.push_back(vec2(550.0f, 220.0f));
    m_CollectableSpawnPoints.push_back(vec2(550.0f, 100.0f));
}

void CGameplayState::createLevel2()
{
    m_GameplayTimer = 15.0f;
    
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
    m_Blocks.push_back(new CBlock(vec2(250, 400), vec2(150, 25), RED));
    m_Blocks.push_back(new CBlock(vec2(650, 550), vec2(150, 25), RED));
    m_Blocks.push_back(new CBlock(vec2(750, 350), vec2(150, 25), RED));
    m_Blocks.push_back(new CBlock(vec2(500, 200), vec2(150, 25), RED));
    m_Blocks.push_back(new CBlock(vec2(250, 300), vec2(150, 25), RED));
    m_Blocks.push_back(new CBlock(vec2(650, 750), vec2(150, 25), RED));
    m_Blocks.push_back(new CBlock(vec2(750, 950), vec2(150, 25), RED));
    m_Blocks.push_back(new CBlock(vec2(500, 500), vec2(150, 25), RED));


    m_CollectableSpawnPoints.push_back(vec2(875.0f, 650.0f));
    m_CollectableSpawnPoints.push_back(vec2(300.0f, 375.0f));
    m_CollectableSpawnPoints.push_back(vec2(550.0f, 220.0f));
    m_CollectableSpawnPoints.push_back(vec2(550.0f, 100.0f));
}

std::vector<CBlock*>& CGameplayState::getBlocks()
{
    return m_Blocks;
}

std::vector<CBall*>& CGameplayState::getBalls()
{
    return m_Balls;
}

std::vector<CCollectable*>& CGameplayState::getCollectables()
{
    return m_Collectables;
}

void CGameplayState::spawnCollectables()
{
    if (m_CollectableSpawnPoints.empty())
    {
        return;
    }

    int randomIndex = GetRandomValue(0, (int)m_CollectableSpawnPoints.size() - 1);

    vec2 position = m_CollectableSpawnPoints[randomIndex];

    CCollectable* collectable = new CCollectable(Game, position);

    m_Collectables.push_back(collectable);
}

void CGameplayState::onKey(int keyCode, KeyState keyState)
{
    if (keyCode == 'R' && keyState == KeyState::Pressed)
    {
        reset();
    }
    if (keyCode == KEY_TAB && keyState == KeyState::Pressed)
    {
        Game->setDebugMode(!Game->getDebugMode());
    }

    if (keyCode == KEY_LEFT_SHIFT && keyState == KeyState::Pressed)
    {
        Game->setLevel2(!Game->getLevel2());
    }

    Player->onKey(keyCode, keyState); // Calling onKey to make the player move.
}

void CGameplayState::onMouseButton(int button, KeyState keyState)
{
    if (button == MOUSE_BUTTON_LEFT && keyState == KeyState::Pressed)
    {
        vec2 mousePosition = { (float)GetMouseX(), (float)GetMouseY() }; // Setting a mouse position so the ball fires in the direction of the mouse

        vec2 direction = mousePosition - Player->getPosition();
        direction.normalize();

        if (m_Balls.size() < 10) // If statement so no more than 10 balls appear on screen at once.
        {
            CBall* newBalls = new CBall(Game,this);

            newBalls->setPosition(Player->getPosition());
            newBalls->setVelocity(direction * 600.0f);
            m_Balls.push_back(newBalls);
        }
    }
}

void CGameplayState::onMouseMove(int x, int y)
{
}
