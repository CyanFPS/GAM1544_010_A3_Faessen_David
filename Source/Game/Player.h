#pragma once

#include "Helpers/Vector.h"
#include "Helpers/InputTypes.h"
#include "Helpers/MathFuncs.h"
#include "Game/AnimatedObject.h"
#include "Block.h"

class CPlatformerGame;
class CBall;
class Sprite2D;

class CPlayer : public CAnimatedObject
{
public:
    CPlayer(CPlatformerGame* game);
    ~CPlayer();

    void update(float deltaTime);
    void draw(vec2 offset);
    
    // Debug Visuals Functions
    void drawDebugVisuals(vec2 offset);
    bool getDebugVisuals();
    void toggleDebugVisuals();
    
    void setPosition(vec2 pos);

    void onKey(int keyCode, KeyState keyState);

    // Collision Code
    void blockCollision(std::vector<CBlock*>& blocks);
    void ballCollision(std::vector<CBall*>& balls);

private:
    
    // Collision points
    vec2 ColliderFootOffset;
    vec2 ColliderLeftOffset;
    vec2 ColliderRightOffset;
    vec2 ColliderHeadOffset;
    
    vec2 Velocity;
    
    
    // Variables for Player movement
    float Speed = 200;
    float MovementDir = 0;
    vec2 Controls;


    // Variable for Ball collision
    bool BallTouching = false;

    bool DebugVisualsEnabled = false;
};
