#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "map.h"
#include "weapon.h"
class Game;
class Map;
class Weapon;

class Player {
private:
    Game* game;

    LevelPos pos;
    Weapon* weapon;

public:
    Player(Game* game, Weapon* weapon);
    ~Player();

    void update();
    void render();

    LevelPos getPos();
    Weapon* getWeapon();
    void setShooting(bool value);
};

#endif
