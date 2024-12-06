#ifndef BULLET_H
#define BULLET_H

#include "game.h"
class Game;

class Bullet {
private:
    Game* game;
    BulletData data;
    LevelPos pos;
    LevelVelocity velocity;

    int reboundsLeft;

public:
    Bullet(Game* game, BulletData data, LevelPos start, LevelVelocity velocity);
    ~Bullet();

    void update();
    void render();
};

#endif
