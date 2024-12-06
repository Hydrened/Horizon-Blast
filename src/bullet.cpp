#include "bullet.h"

// INIT
Bullet::Bullet(Game* g, BulletData d, LevelPos s, LevelVelocity v) : game(g), data(d), pos(s), velocity(v), reboundsLeft(d.rebound) {

}

// CLEANUP
Bullet::~Bullet() {
    Weapon* weapon = game->getMap()->getPlayer()->getWeapon();
    weapon->destroyBullet(this);
}

// UPDATE
void Bullet::update() {
    static GameData* gameData = game->getData();
    Weapon* weapon = game->getMap()->getPlayer()->getWeapon();

    static LevelSize mapSize = gameData->sizes->map;
    static LevelSize bulletSize = gameData->sizes->bullet; 
    static LevelSize itemSize = gameData->sizes->item; 

    if (game->getState() != PLAYING) return;

    // 1 => Update positions
    pos.x += velocity.x * data.speed;
    pos.y += velocity.y * data.speed;

    // 2 => World limits
    if (std::abs(pos.x) > mapSize.w || std::abs(pos.y) > mapSize.h) weapon->destroyBullet(this);

    // 3 => Check wall collisions
    LevelRect bulletRect = getRect(pos, bulletSize);
    for (const Item* item : *(game->getMap()->getItems())) if (item->type != GROUND) {
        LevelRect itemRect = getRect(item->pos, itemSize);
        if (!bulletRect.intersect(itemRect)) continue;

        if (reboundsLeft != 0) {
            switch (bulletRect.getCollidedFace(itemRect)) {
                case NORTH: velocity.y *= -1; pos.y += velocity.y; break;
                case EAST: velocity.x *= -1; pos.x += velocity.x; break;
                case SOUTH: velocity.y *= -1; pos.y += velocity.y; break;
                case WEST: velocity.x *= -1; pos.x += velocity.x; break;
                default: break;
            }
            reboundsLeft--;
        } else weapon->destroyBullet(this);
    }
}

// RENDER
void Bullet::render() {
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();
    static H2DE_Size size = c->convertToPx(gameData->sizes->bullet);

    H2DE_GraphicObject* a = H2DE_CreateGraphicObject();
    a->type = POLYGON;
    a->pos = c->convertToPx(pos, gameData->sizes->bullet);
        a->points = {
        { 0, 0 },
        { size.w, 0 },
        { size.w, size.h },
        { 0, size.h },
    };
    a->rgb = { 0, 255, 0, 255 };
    a->filled = true;
    a->index = 900;
    H2DE_AddGraphicObject(engine, a);
}
