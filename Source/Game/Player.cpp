#include "Player.h"
#include "Block.h"
#include "PlatformerGame.h"
#include "Ball.h"
#include "Helpers/Sprite2D.h"


CPlayer::CPlayer(CPlatformerGame* game) : CAnimatedObject(game) 
{
    Position = { 200, 300 };
    Scale = { 1.5, 1.5 };
    Controls = { 0, 0 };

    ColliderFootOffset = { 0, 50 }; // Foot
    ColliderLeftOffset = { -25, 0 }; // Left Arm
    ColliderRightOffset = { 25, 0 }; // Right Arm
    ColliderHeadOffset = { 0, -25 }; // Head

    // Idle Frame (when player isn't moving)
    IdleFrames.push_back(LoadTexture("Data/Textures/SonicIdle.png"));

    // Moving Animations
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk1.png"));
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk2.png"));
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk3.png"));
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk4.png"));
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk5.png"));
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk6.png"));
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk7.png"));
    WalkFrames.push_back(LoadTexture("Data/Textures/SonicWalk8.png"));

    CurrentFrame = &IdleFrames;
}

CPlayer::~CPlayer()
{
}

void CPlayer::update(float deltaTime)
{
    vec2 gravity = { 0, 250 };
    Velocity += gravity * deltaTime;

    // Movement code
    MovementDir = Controls.X;
    Velocity.X = MovementDir * Speed;

    Position += Velocity * deltaTime;
    
    // If movement is detected; WalkFrames is used.
    if (MovementDir == 0)
    {
        CurrentFrame = &IdleFrames;
    }
    else
    {
        CurrentFrame = &WalkFrames;
    }

    // Flipping Sprites if in the respective axis
    if (MovementDir > 0)
    {
        FlipHorizontal = false;
    }
    if (MovementDir < 0)
    {
        FlipHorizontal = true;
    }

    CAnimatedObject::update(deltaTime);
    
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

    // Ball collision code
    CBall* ball = Game->getBall();
    
    bool touching = IsCircleOverlappingCircle(Position + ColliderFootOffset, 10.0f, ball->getPosition(), ball->getRadius());
    

    if (IsCircleOverlappingCircle(Position + ColliderLeftOffset, 10.0f, ball->getPosition(), ball->getRadius())) // Left Arm Collision
    {
        touching = true;
    }
    if (IsCircleOverlappingCircle(Position + ColliderRightOffset, 10.0f, ball->getPosition(), ball->getRadius())) // Right Arm Collision
    {
        touching = true;
    }
    if (IsCircleOverlappingCircle(Position + ColliderHeadOffset, 10.0f, ball->getPosition(), ball->getRadius())) // Head Collision
    {
        touching = true;
    }

    if (touching && !BallTouching)
    {
        vec2 velocity = ball->getVelocity();

        velocity.Y -= 250.0f;

        ball->setVelocity(velocity);
    }

    BallTouching = touching;
}
void CPlayer::draw()
{
    CAnimatedObject::draw();
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


