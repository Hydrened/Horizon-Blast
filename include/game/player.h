#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "map.h"
class Game;
class Map;

class Player {
private:
    Game* game;
    Map* map;

    LevelPos pos = { 0, 0 };

public:
    Player(Game* game, Map* map);
    ~Player();

    void update();
    void render();

    void shot(LevelPos pos);
};

#endif
