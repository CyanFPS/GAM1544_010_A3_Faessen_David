#pragma once
#include "raylib.h"
#include "Helpers/Vector.h"
#include "Helpers/Sprite2D.h"
#include "Game/PlatformerGame.h"

class CPlatformerGame;
class Sprite2D;

class CCollectable
{
public:
    // Constructor and Deconstructor 
    CCollectable(CPlatformerGame* game,vec2 position);
    ~CCollectable();

    void draw();

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
};