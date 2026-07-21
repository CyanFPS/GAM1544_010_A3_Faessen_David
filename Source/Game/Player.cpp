#include "Player.h"
#include "Block.h"
#include "PlatformerGame.h"

CPlayer::CPlayer(CPlatformerGame* game)
    : Game( game ),
      m_Speed(200.0f)
{
    Position = { 200, 300 };
    Scale = { 50, 100 };
    Controls = { 0, 0 };

    ColliderFootOffset = { 0, 50 }; // Foot
    ColliderLeftOffset = { -25, 0 }; // Left Arm
    ColliderRightOffset = { 25, 0 }; // Right Arm
    ColliderHeadOffset = { 0, -50 }; // Head
}

CPlayer::~CPlayer()
{
}

void CPlayer::update(float deltaTime)
{
    
    Velocity.X = Controls.X * m_Speed; // Movement Vector Math
    
    vec2 gravity = { 0, 75 };
    
    Velocity += gravity * deltaTime;
    Position += Velocity * deltaTime;

    // Asking for the blocks
    std::vector<CBlock*>& m_Blocks = Game->getBlocks();
    
    // Loop over blocks, check for overlaps
    for (CBlock* block : m_Blocks)
    {
        if (block->getAABB().isPointInside(Position + ColliderFootOffset)) // Foot Collision
        {
            Position.Y = block->getPosition().Y - 50;
            Velocity.Y = 0;
        }
       if (block->getAABB().isPointInside(Position + ColliderLeftOffset)) // Left Side Collision
        {
           Position.X = block->getPosition().X + block->getSize().X + Scale.X / 2;
           Velocity.X = 0;
        }
        if (block->getAABB().isPointInside(Position + ColliderRightOffset)) // Right Side Collision
        {
            Position.X = block->getPosition().X - Scale.X / 2;
            Velocity.X = 0;
        }
        if (block->getAABB().isPointInside(Position + ColliderHeadOffset)) // Head Collision
        {
            Position.Y = block->getPosition().Y + 50;
            Velocity.Y = 0;
        }
    }
}

void CPlayer::draw()
{
    DrawRectangle(
        Position.X - Scale.X/2,
        Position.Y - Scale.Y/2,
        Scale.X, Scale.Y, YELLOW );
}

void CPlayer::drawDebugVisuals()
{
    DrawCircle(
        Position.X + ColliderFootOffset.X,
        Position.Y + ColliderFootOffset.Y,
        5, { 255, 109, 194, 200 });
    DrawCircle(
        Position.X + ColliderLeftOffset.X,
        Position.Y + ColliderLeftOffset.Y,
        5, { 255, 109, 194, 200 });
    DrawCircle(
        Position.X + ColliderRightOffset.X,
        Position.Y + ColliderRightOffset.Y,
        5, { 255, 109, 194, 200 });
    DrawCircle(
        Position.X + ColliderHeadOffset.X,
        Position.Y + ColliderHeadOffset.Y,
        5, { 255, 109, 194, 200 });
}

void CPlayer::setPosition(vec2 pos)
{
    Position = pos;
}

void CPlayer::onKey(int keyCode, KeyState keyState)
{
    
    if (keyState == KeyState::Pressed)
    {
        if (keyCode == KEY_LEFT || keyCode == 'A')
            Controls.X -= 1;
        if (keyCode == KEY_RIGHT || keyCode == 'D')
            Controls.X += 1;
    }

    if (keyState == KeyState::Released)
    {
        if (keyCode == KEY_LEFT || keyCode == 'A')
            Controls.X += 1;
        if (keyCode == KEY_RIGHT || keyCode == 'D')
            Controls.X -= 1;
    }
}


