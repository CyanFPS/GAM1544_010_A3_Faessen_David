#pragma once
#include <vector>
#include "Game/PlatformerGame.h"
#include "Game/GameObject.h"
#include "Helpers/Sprite2D.h"
#include "Helpers/Vector.h"

class CAnimatedObject : public CGameObject
{
public:
    CAnimatedObject(CPlatformerGame* game);

    virtual void update(float deltaTime);
    virtual void draw(vec2 offset);

protected:
    Sprite2D Sprite;

    std::vector<Texture2D> WalkFrames;
    std::vector<Texture2D> IdleFrames;

    std::vector<Texture2D>* CurrentFrame;

    float AnimationTimer;
    float FrameTime;

    bool FlipHorizontal = false;
};