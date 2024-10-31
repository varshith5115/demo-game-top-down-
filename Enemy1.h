#ifndef ENEMY1_H
#define ENEMY1_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "character.h"

class Enemy1 : public BaseCharacter
{
public:
    Enemy1(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    void setTarget(character* Character) {target = Character;}
    virtual Vector2 getScreenPos() override;

private:
    character* target;
    float damagePerSec{10.f};
    float radius{25.f};

};

#endif 
