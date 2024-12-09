#include "bullet.h"

// INIT
Bullet::Bullet(Game* g, Weapon* w, BulletData d, LevelPos s, LevelVelocity v) : game(g), weapon(w), data(d), pos(s), velocity(v), reboundsLeft(d.rebound) {
    velocity.x *= data.speed;
    velocity.y *= data.speed;
}

// CLEANUP
Bullet::~Bullet() {
    Weapon* weapon = game->getMap()->getPlayer()->getWeapon();
    weapon->destroyBullet(this);
}

// UPDATE
void Bullet::update() {
    static GameData* gameData = game->getData();

    static LevelSize mapSize = gameData->sizes->map;
    static LevelSize bulletSize = gameData->sizes->bullet; 
    static LevelSize itemSize = gameData->sizes->item; 

    if (game->getState() == PLAYING) {
        // 1 => Update positions
        pos.x += velocity.x;
        pos.y += velocity.y;

        // 2 => World limits
        if (std::abs(pos.x) > mapSize.w || std::abs(pos.y) > mapSize.h) weapon->destroyBullet(this);

        // 3 => Check wall collisions
        LevelRect bulletRect = getRect(pos, bulletSize);
        for (const Item* item : *(game->getMap()->getItems())) if (item->type == WALL) {
            LevelRect itemRect = getRect(item->pos, itemSize);
            if (!bulletRect.intersect(itemRect, velocity)) continue;

            if (reboundsLeft != 0) {
                switch (bulletRect.getCollidedFace(itemRect, velocity)) {
                    case NORTH: velocity.y *= -1; break;
                    case EAST: velocity.x *= -1; break;
                    case SOUTH: velocity.y *= -1; break;
                    case WEST: velocity.x *= -1; break;
                    default: break;
                }
                reboundsLeft--;
                break;
            } else weapon->destroyBullet(this);
        }

        // 4 => Check canDamage collisions
        for (Entity* entity : *(game->getMap()->getEntities())) {
            if (entity->isDead()) continue;
            LevelRect entityRect = getRect(entity->getPos(), entity->getSize());
            if (!bulletRect.intersect(entityRect, velocity)) continue;

            bool canDamage = false;
            switch (data.canDamage) {
                case PLAYER: canDamage = (EntityCaster::castToPlayer(entity) != nullptr); break;
                case ENEMY: canDamage = (EntityCaster::castToEnemy(entity) != nullptr); break;
                default: break;
            }

            if (!canDamage) continue;
            entity->decreaseHealth(data.damage);
            if (!data.pierce) weapon->destroyBullet(this);
        }
    }
}

// RENDER
void Bullet::render() {
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();
    static Camera* camera = game->getCamera();
    static GameData* gameData = game->getData();
    static H2DE_Size size = c->convertToPx(gameData->sizes->bullet);

    if (camera->contains(getRect(pos, gameData->sizes->bullet))) {
        H2DE_GraphicObject* a = H2DE_CreateGraphicObject();
        a->type = POLYGON;
        a->pos = c->convertToPx(pos, gameData->sizes->bullet);
            a->points = {
            { 0, 0 },
            { size.w, 0 },
            { size.w, size.h },
            { 0, size.h },
        };
        a->rgb = { 128, 128, 255, 255 };
        a->filled = true;
        a->index = 9;
        H2DE_AddGraphicObject(engine, a);
    }
}
