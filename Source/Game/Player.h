#pragma once

#include "Helpers/Vector.h"
#include "Helpers/InputTypes.h"
#include "Helpers/MathFuncs.h"
#include "Game/AnimatedObject.h"

class CPlatformerGame;
class CBall;
class Sprite2D;

class CPlayer : public CAnimatedObject
{
public:
    CPlayer(CPlatformerGame* game);
    ~CPlayer();

    void update(float deltaTime);
    void draw();
    void drawDebugVisuals();
    bool getDebugVisuals();

    void setPosition(vec2 pos);

    void onKey(int keyCode, KeyState keyState);

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
