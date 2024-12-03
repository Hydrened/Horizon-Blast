#include "map.h"

// INIT
Map::Map(Game* g) : game(g) {
    loadData();
    player = new Player(g, this);
}

void Map::loadData() {

}

// CLEANUP
Map::~Map() {

}

// UPDATE
void Map::update() {
    player->update();
}

// RENDER
void Map::render() {
    player->render();
}

// GETTER
Player* Map::getPlayer() {
    return player;
}
