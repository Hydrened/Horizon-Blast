#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "map.h"
#include "bullet.h"
class Game;
class Map;
class Bullet;

class Player {
private:
    Game* game;
    Map* map;

    LevelPos pos;
    std::vector<Bullet*> bullets;

public:
    Player(Game* game, Map* map);
    ~Player();

    void update();
    void render();

    void shot(LevelPos pos);

    std::vector<Bullet*>* getBullets();
};

#endif
