#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "player.h"
class Game;
class Player;

class Map {
private:
    Game* game;

    std::unordered_map<unsigned int, LevelData*> levels;
    Player* player;
    std::vector<Item*> items;

    void loadData();

public:
    Map(Game* game);
    ~Map();

    void update();
    void render();

    Player* getPlayer();
    std::vector<Item*>* getItems();
};

#endif
