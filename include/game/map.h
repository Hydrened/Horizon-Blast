#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "entity.h"
class Game;
class Player;
class Enemy;

class Map {
private:
    Game* game;

    std::unordered_map<unsigned int, LevelData*> levels;
    std::vector<Item*> items;
    Player* player;
    std::vector<Enemy*> enemies;

    void loadData();

public:
    Map(Game* game);
    ~Map();

    void update();
    void render();

    Player* getPlayer() const;
    std::vector<Item*>* getItems();
};

#endif
