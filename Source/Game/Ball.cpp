#include "Ball.h"
#include "PlatformerGame.h"
#include "Collectable.h"
#include "GameplayState.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"


CBall::CBall(CPlatformerGame* game,CGameplayState* state)
    : Game(game), State(state)
{
    Active = true;

    Radius = 32.0f;
    Scale = 1.0f;
    MaxTime = 3.5f; // Ball lasts 3.5 seconds
    Lifetime = MaxTime;

    Sprite = new Sprite2D(Game->getTexture("SoccerBall"));
}

CBall::~CBall()
{
    delete Sprite;
}

void CBall::reset()
{
    setActive(false);
}

void CBall::update(float deltaTime)
{
    // Code for the Lifetime of the Ball
    Lifetime -= deltaTime;
    Scale = Lifetime / MaxTime;

    if (Lifetime <= 0.0f)
    {
        Active = false;
        return;
    }
    
    float speed = 150.0f;
    vec2 gravity = { 0.0f, 200.0f };

    Position.X += Velocity.X * deltaTime;
    Position.Y += Velocity.Y * deltaTime;

    Angle += deltaTime * Velocity.X;


    // Lock to edges.
    if (Position.X < 32.0f)
    {
        Position.X = 32.0f;
        Velocity.X *= -0.95f; // Bounce off the left edge.
    }
    if (Position.X >= GetScreenWidth() - 32.0f)
    {
        Position.X = GetScreenWidth() - 32.0f;
        Velocity.X *= -0.95f; // Bounce off the right edge.
    }
    if (Position.Y < 32.0f)
    {
        Position.Y = 32.0f;
        Velocity.X *= 0.95f; // Slow down horizontal velocity.
        Velocity.Y *= -0.95f; // Bounce off the top.
    }
    if (Position.Y >= GetScreenHeight() - 32.0f)
    {
        Position.Y = GetScreenHeight() - 32.0f;
        Velocity.X *= 0.95f; // Slow down horizontal velocity.
        Velocity.Y *= -0.95f; // Bounce off the bottom.
    }

    blockCollision();
    collectableCollision();
}

void CBall::draw(vec2 offset)
{
    Sprite->draw(Position + offset, Angle, Scale, FlipHorizontal);
}

void CBall::blockCollision()
{
    for (CBlock* block : State->getBlocks()) // For loop to check for overlaps with the blocks
    {
        // Setting the position and size from the Getters in the Block class
        vec2 position = block->getPosition();
        vec2 size = block->getSize();

        // Defining each blocks edges for the ball collision
        vec2 topLeft = position;
        vec2 topRight = { position.X + size.X, position.Y };
        vec2 bottomLeft = { position.X, position.Y + size.Y };
        vec2 bottomRight = { position.X + size.X, position.Y + size.Y };

        if (IsCircleOverlappingLine(topLeft, topRight, Position, Radius)) // Top Edge
        {
            Position.Y = position.Y - 32.0f;
            Velocity.Y *= -0.5f;
        }
        if (IsCircleOverlappingLine(bottomLeft, bottomRight, Position, Radius)) // Bottom Edge
        {
            Position.Y = position.Y + size.Y + 32.0f;
            Velocity.Y *= -0.5f;
        }
        if (IsCircleOverlappingLine(topLeft, bottomLeft, Position, Radius)) // Left Edge
        {
            Position.X = position.X - 32.0f;
            Velocity.X *= -0.5f;
        }
        if (IsCircleOverlappingLine(topRight, bottomRight, Position, Radius)) // Right Edge
        {
            Position.X = position.X + size.X + 32.0f;
            Velocity.X *= -0.5f;
        }
    }
}

void CBall::collectableCollision()
{
    for (CCollectable* collectable : State->getCollectables())
    {
        if (IsCircleOverlappingCircle(Position, 32.0f, collectable->getPosition(), collectable->getRadius()))
        {
            Game->AddCollectedCount();
            collectable->isCollected();
            collectable->respawn();
        }
    }
}

void CBall::onKey(int keyCode, KeyState keyState)
{
    if (IsWindowFocused() == false)
        Controls = 0;

    if (keyState == KeyState::Pressed)
    {
        if (keyCode == KEY_UP || keyCode == 'W')
            Controls.Y -= 1;
        if (keyCode == KEY_DOWN || keyCode == 'S')
            Controls.Y += 1;
        if (keyCode == KEY_LEFT || keyCode == 'A')
            Controls.X -= 1;
        if (keyCode == KEY_RIGHT || keyCode == 'D')
            Controls.X += 1;
    }

    if (keyState == KeyState::Released)
    {
        if (keyCode == KEY_UP || keyCode == 'W')
            Controls.Y += 1;
        if (keyCode == KEY_DOWN || keyCode == 'S')
            Controls.Y -= 1;
        if (keyCode == KEY_LEFT || keyCode == 'A')
            Controls.X += 1;
        if (keyCode == KEY_RIGHT || keyCode == 'D')
            Controls.X -= 1;
    }
}