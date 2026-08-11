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
	Player = nullptr;
	Ball = nullptr;

	m_CollectableSpawnTimer = 0.0f;
	m_CollectableSpawnInterval = 3.0f;

	Player = new CPlayer(Game);
	Ball = new CBall(Game);

	m_Balls.push_back(Ball);

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
    m_Blocks.push_back(new CBlock(vec2(750, 500), vec2(150, 25), DARKBLUE));
    m_Blocks.push_back(new CBlock(vec2(750, 200), vec2(150, 25), DARKBLUE));
    m_Blocks.push_back(new CBlock(vec2(250, 100), vec2(150, 25), DARKBLUE));
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
    
    if (Player != nullptr)
    {
        Player->update(deltaTime);
    }

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

void CGameplayState::draw()
{
    ClearBackground(WHITE);
    DrawText(TextFormat("Collected: %i", Game->CountCollectables()), 900, 600, 50, DARKBLUE);

    Player->draw();

    // Drawing Debug Visuals
    if (Player->getDebugVisuals())
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

void CGameplayState::reset()
{
    Player->setPosition({ 200,300 });
}

void CGameplayState::onActivate()
{
}

void CGameplayState::onDeactive()
{
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

CBall* CGameplayState::getBall()
{
    return Ball;
}

void CGameplayState::onKey(int keyCode, KeyState keyState)
{
    if (keyCode == 'R' && keyState == KeyState::Pressed)
    {
        reset();
    }
    if (keyCode == KEY_TAB && keyState == KeyState::Pressed)
    {
        Player->getDebugVisuals();
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
            CBall* newBalls = new CBall(Game);

            newBalls->setPosition(Player->getPosition());
            newBalls->setVelocity(direction * 600.0f);
            m_Balls.push_back(newBalls);
        }
    }
}

void CGameplayState::onMouseMove(int x, int y)
{
}
