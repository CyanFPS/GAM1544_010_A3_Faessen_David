#include "AnimatedObject.h"

CAnimatedObject::CAnimatedObject(CPlatformerGame* game) : CGameObject(game)
{
    CurrentFrame = &IdleFrames;
    AnimationTimer = 0.0f;
    FrameTime = 0.1f;
}

void CAnimatedObject::update(float deltaTime)
{
    AnimationTimer += deltaTime; // every frame adds 1.0 to AnimationTimer

    if (CurrentFrame->empty()) // Prevents the game crashing if no texture is found
    {
        return;
    }

    int frame = (int)(AnimationTimer / FrameTime); // Taking the time and converting it into the frame number.

    frame %= CurrentFrame->size(); // Resetting the animation when FrameTime has reached it's end

    Sprite.setTexture((*CurrentFrame)[frame]);
}

void CAnimatedObject::draw()
{
    Sprite.draw(Position, Angle, Scale, FlipHorizontal);
}