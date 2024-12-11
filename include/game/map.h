#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "entity.h"
class Game;
class Entity;
class Player;

class Map {
private:
    Game* game;

    std::vector<Item*> items;
    Player* player;
    std::vector<Entity*> entities;
    unsigned int levelID;

    void initPlayer();

public:
    Map(Game* game);
    ~Map();

    void update();
    void render();

    void openLevel(unsigned int id);
    void destroyEntity(Entity* entity);

    Player* getPlayer() const;
    std::vector<Item*>* getItems();
    std::vector<Entity*>* getEntities();
    unsigned int getCurrentLevelId();
    bool areAllEnemyDead();
};

#endif
