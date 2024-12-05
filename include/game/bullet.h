#ifndef BULLET_H
#define BULLET_H

#include "game.h"
class Game;

class Bullet {
private:
    Game* game;
    LevelPos start;
    LevelPos end;
    LevelPos pos;
    BulletData data;

    H2DE_TimelineManager* tm = H2DE_CreateTimelineManager();

public:
    Bullet(Game* game, BulletData data, LevelPos start, LevelPos end);
    ~Bullet();

    void update();
    void render();
};

#endif
