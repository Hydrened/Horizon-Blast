#include "map.h"

// INIT
Map::Map(Game* g) : game(g) {
    static GameData* gameData = game->getData();

    loadData();

    BulletData pbd1 = BulletData();
    pbd1.canDamage = ENEMY;
    pbd1.damage = 1.0f;
    pbd1.speed = 3.0f;
    pbd1.rebound = 1;
    pbd1.angle = 0.0f;

    BulletData pbd2 = BulletData(pbd1);
    pbd2.angle = 5.0f;

    BulletData pbd3 = BulletData(pbd1);
    pbd3.angle = -5.0f;

    WeaponData pwd = WeaponData();
    pwd.delay = 500;
    pwd.bullets = { pbd1, pbd2, pbd3 };

    EntityData playerData = { 10.0f, gameData->positions->player };
    player = new Player(g, playerData);
    entities.push_back(player);

    Weapon* playerWeapon = new Weapon(g, player, pwd);
    player->setWeapon(playerWeapon);



    std::vector<LevelPos> enemyPositions = { { 5.0f, 3.0f } };
    for (LevelPos ePos : enemyPositions) {
        EntityData enemyData = { 10.0f, ePos };
        Enemy* enemy = new Enemy(g, enemyData);

        WeaponData ewd = WeaponData(pwd);
        BulletData ebd = BulletData(pbd1);
        ebd.canDamage = PLAYER;
        ebd.speed = 1.0f;
        ewd.bullets = { ebd };
        Weapon* enemyWeapon = new Weapon(g, enemy, ewd);
        enemy->setWeapon(enemyWeapon);

        entities.push_back(enemy);
    }
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
    for (Entity* e : entities) delete e;
    entities.clear();
    for (Item* i : items) delete i;
    items.clear();
    for (const auto& [key, value] : levels) {
        delete value;
        levels[key] = nullptr;
    }
    levels.clear();
}

// UPDATE
void Map::update() {
    for (Entity* e : entities) e->update();
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

    for (Entity* e : entities) e->render();
}

// EVENTS
void Map::destroyEntity(Entity* entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) entities.erase(it);
}

// GETTER
Player* Map::getPlayer() const {
    return player;
}

std::vector<Item*>* Map::getItems() {
    return &items;
}

std::vector<Entity*>* Map::getEntities() {
    return &entities;
}
