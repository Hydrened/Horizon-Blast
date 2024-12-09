#include "map.h"

// INIT
Map::Map(Game* g) : game(g) {
    initPlayer();
    openLevel(1);
}

void Map::initPlayer() {
    static GameData* gameData = game->getData();

    EntityData playerData = { 10.0f, gameData->positions->player };
    player = new Player(game, playerData);
    entities.push_back(player);

    WeaponData weaponData = WeaponData();
    weaponData.delay = 500;

    BulletData bulletData1 = BulletData();
    bulletData1.canDamage = ENEMY;
    bulletData1.damage = 1.0f;
    bulletData1.speed = 3.0f;
    bulletData1.rebound = 1;
    bulletData1.angle = 0.0f;
    weaponData.bullets.push_back(bulletData1);

    BulletData bulletData2 = BulletData(bulletData1);
    bulletData2.angle = 5.0f;
    weaponData.bullets.push_back(bulletData2);

    BulletData bulletData3 = BulletData(bulletData1);
    bulletData3.angle = -5.0f;
    weaponData.bullets.push_back(bulletData3);

    Weapon* weapon = new Weapon(game, player, weaponData);
    player->setWeapon(weapon);
}

// CLEANUP
Map::~Map() {
    for (Entity* e : entities) delete e;
    entities.clear();
    
    for (Item* i : items) delete i;
    items.clear();
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
void Map::openLevel(unsigned int id) {
    static GameData* gameData = game->getData();

    for (const Item* item : items) delete item;
    items.clear();

    for (Entity* entity : entities) {
        Enemy* enemy = EntityCaster::castToEnemy(entity);
        if (enemy) delete enemy;
    }

    game->getCamera()->setPos(gameData->positions->camera);
    player->resetPos();
    player->getWeapon()->reset();

    std::cout << "Opening level " << id << std::endl;
    levelID = id;
    json* levels = H2DE_Json::read("data/levels.json");
    json level = (*levels)[std::to_string(id)];

    for (json i : level["items"]) {
        Item* item = new Item();
        item->type = i["t"];
        item->pos = { i["x"], i["y"] };
        items.push_back(item);
    }

    for (json e : level["enemies"]) {
        EntityData enemyData = { e["health"], { e["pos"]["x"], e["pos"]["y"] } };
        Enemy* enemy = new Enemy(game, enemyData);
        entities.push_back(enemy);

        json w = e["weapon"];
        WeaponData weaponData = WeaponData();
        weaponData.delay = w["delay"];

        for (json bullet : w["bullets"]) {
            BulletData bulletData = BulletData();
            bulletData.canDamage = PLAYER;
            bulletData.speed = bullet["speed"];
            bulletData.damage = bullet["damage"];
            bulletData.rebound = bullet["rebound"];
            bulletData.pierce = bullet["pierce"];
            bulletData.explosive = bullet["explosive"];
            bulletData.angle = bullet["angle"];
            weaponData.bullets.push_back(bulletData);
        }

        Weapon* weapon = new Weapon(game, enemy, weaponData);
        enemy->setWeapon(weapon);
    }
}

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

unsigned int Map::getCurrentLevelId() {
    return levelID;
}
