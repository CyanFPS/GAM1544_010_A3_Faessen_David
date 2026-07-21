#pragma once

#include "Helpers/Vector.h"
#include "Helpers/InputTypes.h"

class CPlatformerGame;

class CPlayer
{
public:
    CPlayer(CPlatformerGame* game);
    ~CPlayer();

    void update(float deltaTime);
    void draw();
    void drawDebugVisuals();

    void setPosition(vec2 pos);

    void onKey(int keyCode, KeyState keyState);

private:
    CPlatformerGame* Game;
    
    // Collision points
    vec2 ColliderFootOffset;
    vec2 ColliderLeftOffset;
    vec2 ColliderRightOffset;
    vec2 ColliderHeadOffset;
    
    
    vec2 Position;
    vec2 Scale;
    vec2 Velocity;
    
    
    // Variables for Player movement
    const float m_Speed;
    vec2 Controls;
};
