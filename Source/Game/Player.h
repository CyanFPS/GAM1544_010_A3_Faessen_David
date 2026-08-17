#pragma once

#include "Helpers/Vector.h"
#include "Helpers/InputTypes.h"
#include "Helpers/MathFuncs.h"
#include "Game/AnimatedObject.h"
#include "Block.h"
#include "Collectable.h"

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
    void collectableCollision(std::vector<CCollectable*>& collectables);

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
    float Jump = -300.0f;
    vec2 Controls;


    // Variables for collisions
    bool BallTouching = false;

    bool DebugVisualsEnabled = false;

    // Bool to determine when player is on ground or not for smoother jumping
    bool OnGround = false;
};
