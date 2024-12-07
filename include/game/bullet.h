#ifndef BULLET_H
#define BULLET_H

#include "game.h"
#include "weapon.h"
class Game;
class Weapon;

class Bullet {
private:
    Game* game;
    Weapon* weapon;
    BulletData data;
    LevelPos pos;
    LevelVelocity velocity;

    int reboundsLeft;

public:
    Bullet(Game* game, Weapon* weapon, BulletData data, LevelPos start, LevelVelocity velocity);
    ~Bullet();

    void update();
    void render();
};

#endif
