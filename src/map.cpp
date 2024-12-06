#include "map.h"

// INIT
Map::Map(Game* g) : game(g) {
    loadData();

    BulletData bulletData = BulletData();
    bulletData.damage = 1.0f;
    bulletData.speed = 2.0f;
    bulletData.rebound = 10;

    WeaponData weaponData = WeaponData();
    weaponData.delay = 100;
    weaponData.bullets = { bulletData };

    Weapon* weapon = new Weapon(g, weaponData);
    player = new Player(g, weapon);
}

void Map::loadData() {
    json* levels = H2DE_Json::read("data/levels.json");
    json level = (*levels)["0"];

    for (json i : level) {
        Item* item = new Item();
        item->type = i["t"];
        item->pos = { i["x"], i["y"] };
        items.push_back(item);
    }
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
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();

    static LevelSize itemSize = gameData->sizes->item;
    static H2DE_Size absItemSize = c->convertToPx(itemSize);

    for (Item* item : items) {
        H2DE_GraphicObject* i = H2DE_CreateGraphicObject();
        i->type = POLYGON;
        i->pos = c->convertToPx(item->pos, itemSize);
        i->points = {
            { 0, 0 },
            { absItemSize.w, 0 },
            { absItemSize.w, absItemSize.h },
            { 0, absItemSize.h },
        };
        i->rgb = (item->type == WALL) ? H2DE_RGB{ 255, 255, 255, 255 } : (item->type == GROUND) ? H2DE_RGB{ 50, 50, 50, 255 } : H2DE_RGB{ 0, 0, 0, 255 };
        i->filled = true;
        i->index = (item->type == WALL) ? 15 : 1;
        H2DE_AddGraphicObject(engine, i);
    }

    player->render();
}

// GETTER
Player* Map::getPlayer() {
    return player;
}

std::vector<Item*>* Map::getItems() {
    return &items;
}
