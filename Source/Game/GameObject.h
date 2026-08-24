#pragma once
#include "../Game/PlatformerGame.h"
#include "raylib.h"
#include "..//Helpers/Vector.h"
#include "..//Helpers/InputTypes.h"

class CPlatformerGame;

class CGameObject
{
public:
    CGameObject();
    ~CGameObject();
    CGameObject(CPlatformerGame* game);

    virtual void onKey(int keyCode, KeyState keyState);
    virtual void update(float deltaTime) = 0;
    virtual void draw(vec2 offset) = 0;

    vec2 getPosition() { return Position; }
    void setPosition(vec2 pos) { Position = pos; }

protected:
    CPlatformerGame* Game;

    vec2 Position;
    float Angle = 0;
    vec2 Scale = 1;

    Color ObjectColor = RED;
};