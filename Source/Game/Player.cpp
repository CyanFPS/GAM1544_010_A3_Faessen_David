#include "Player.h"
#include "Block.h"
#include "PlatformerGame.h"
#include "Ball.h"
#include "Helpers/Sprite2D.h"
#include "Collectable.h"


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

    // Jump Frame
    JumpFrame.push_back(LoadTexture("Data/Textures/SonicJump.png"));

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
    
    //If movement is detected; WalkFrames is used.
    if (MovementDir == 0)
    {
        CurrentFrame = &IdleFrames;
    }
    else
    {
        CurrentFrame = &WalkFrames;
    }

    if (!OnGround)
    {
        CurrentFrame = &JumpFrame;
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
}
void CPlayer::draw(vec2 offset)
{
    CAnimatedObject::draw(offset);
}

void CPlayer::drawDebugVisuals(vec2 offset)
{
    DrawCircle(
        Position.X + ColliderFootOffset.X + offset.X,
        Position.Y + ColliderFootOffset.Y + offset.Y,
        5, { 255, 109, 194, 200 });
    DrawCircle(
        Position.X + ColliderLeftOffset.X + offset.X,
        Position.Y + ColliderLeftOffset.Y + offset.Y,
        5, { 255, 109, 194, 200 });
    DrawCircle(
        Position.X + ColliderRightOffset.X + offset.X,
        Position.Y + ColliderRightOffset.Y + offset.Y,
        5, { 255, 109, 194, 200 });
    DrawCircle(
        Position.X + ColliderHeadOffset.X + offset.X,
        Position.Y + ColliderHeadOffset.Y + offset.Y,
        5, { 255, 109, 194, 200 });
}

bool CPlayer::getDebugVisuals()
{
    return DebugVisualsEnabled;
}

void CPlayer::toggleDebugVisuals()
{
    DebugVisualsEnabled = !DebugVisualsEnabled;
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

    if (keyCode == KEY_SPACE && keyState == KeyState::Pressed && OnGround)
    {
        Velocity.Y = Jump;
        OnGround = false;
    }
}

void CPlayer::blockCollision(std::vector<CBlock*>& blocks)
{
    OnGround = false;
   
    // Loop over blocks, check for overlaps
    for (CBlock* block : blocks)
    {
        if (block->getAABB().isPointInside(Position + ColliderFootOffset)) // Foot Collision
        {
            Position.Y = block->getPosition().Y - 50;
            Velocity.Y = 0;

            OnGround = true;
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

void CPlayer::ballCollision(std::vector<CBall*>& balls)
{   // Looping over balls
    for (CBall* ball : balls)
    {
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
}

void CPlayer::collectableCollision(std::vector<CCollectable*>& collectables)
{
    for (CCollectable* collectable : collectables)
    {
        if (collectable->isCollected())
        {
            continue;
        }
        
        bool touching = false;

        if (IsCircleOverlappingCircle(Position + ColliderFootOffset, 10.0f, collectable->getPosition(), collectable->getRadius())) // Foot Collision
        {
            touching = true;
        }
        
        if (IsCircleOverlappingCircle(Position + ColliderLeftOffset, 10.0f, collectable->getPosition(), collectable->getRadius())) // Left Arm Collision
        {
            touching = true;
        }
        if (IsCircleOverlappingCircle(Position + ColliderRightOffset, 10.0f, collectable->getPosition(), collectable->getRadius())) // Right Arm Collision
        {
            touching = true;
        }
        if (IsCircleOverlappingCircle(Position + ColliderHeadOffset, 10.0f, collectable->getPosition(), collectable ->getRadius())) // Head Collision
        {
            touching = true;
        }

        if (touching)
        {
            collectable->setCollected(true);
            Game->AddCollectedCount();
        }
    }
}


