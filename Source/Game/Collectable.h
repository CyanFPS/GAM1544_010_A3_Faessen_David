#pragma once
#include "raylib.h"
#include "..//Helpers/Vector.h"
#include "..//Helpers/Sprite2D.h"
#include "..//Helpers/Easing.h"
#include "..//Game/PlatformerGame.h"

class CPlatformerGame;
class Sprite2D;

class CCollectable
{
public:
    // Constructor and Deconstructor 
    CCollectable(CPlatformerGame* game,vec2 position);
    ~CCollectable();

    void draw(vec2 offset);
    void update(float deltaTime);

    // Getters
    vec2 getPosition();
    float getRadius();

   // Functions to collect the collectables
    bool isCollected();
    void setCollected(bool collected);
    void respawn();
   
private:
    CPlatformerGame* Game;
    
    vec2 m_Position;
    float m_Radius;
    bool m_Collected;

    Sprite2D* Sprite;

    // Easing Variables
    float m_AnimationTimer;
    float m_AnimationDuration;
    vec2 m_OriginalPosition;
};