#include "entity.h"

// ENTITY
// INIT
Entity::Entity(Game* g, EntityData d) : game(g), data(d), health(d.health), pos(d.pos) {

}

// CLEANUP
Entity::~Entity() {
    delete weapon;
}

// RENDER
bool Entity::renderHealthBarBG() {
    static H2DE_Engine* engine = game->getEngine();
    static Camera* camera = game->getCamera();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();

    static H2DE_Size size = c->convertToPx(gameData->sizes->healthBar);

    if (camera->contains(getRect(pos, gameData->sizes->healthBar))) {
        H2DE_GraphicObject* bg = H2DE_CreateGraphicObject();
        bg->type = POLYGON;
        bg->pos = c->convertToPx(pos + gameData->offsets->healthBar, gameData->sizes->healthBar);
        bg->points = {
            { 0, 0 },
            { size.w, 0 },
            { size.w, size.h },
            { 0, size.h },
        };
        bg->rgb = { 50, 50, 50, 255 };
        bg->filled = true;
        bg->index = 50;
        H2DE_AddGraphicObject(engine, bg);
        return true;
    } else return false;
}

void Entity::renderHealthBarPoints(H2DE_RGB rgb) {
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();

    float blend = health / data.health;
    if (blend > 0.0f) {
        H2DE_Size size = c->convertToPx({ gameData->sizes->healthBar.w * blend, gameData->sizes->healthBar.h });

        H2DE_GraphicObject* points = H2DE_CreateGraphicObject();
        points->type = POLYGON;
        points->pos = c->convertToPx(pos + gameData->offsets->healthBar, gameData->sizes->healthBar);
        points->points = {
            { 0, 0 },
            { size.w, 0 },
            { size.w, size.h },
            { 0, size.h },
        };
        points->rgb = rgb;
        points->filled = true;
        points->index = 51;
        H2DE_AddGraphicObject(engine, points);
    }
}

// EVENTS
void Entity::decreaseHealth(float damage) {
    health = std::max(0.0f, health - damage);
    if (health == 0.0f) kill();
}

// GETTER
LevelPos Entity::getPos() const {
    return pos;
}

Weapon* Entity::getWeapon() const {
    return weapon;
}

LevelPos Entity::getTarget() const {
    return target;
}



// PLAYER
// INIT
Player::Player(Game* g, EntityData d) : Entity(g, d) {

}
// CLEANUP
Player::~Player() {

}

// UPDATE
void Player::update() {
    static Calculator* c = game->getCalculator();
    static Camera* camera = game->getCamera();
    static GameData* gameData = game->getData();

    static float speed = gameData->physics->playerSpeed;
    static float camPadding = gameData->sizes->cameraPadding;
    static LevelSize playerSize = gameData->sizes->player;
    static LevelSize itemSize = gameData->sizes->item;

    if (game->getState() == PLAYING) {
        // 1 => Movements
        for (const SDL_Keycode key : game->getPressedKeys()) switch (key) {
            case SDLK_UP: pos.y += speed; break;
            case SDLK_RIGHT: pos.x += speed; break;
            case SDLK_DOWN: pos.y -= speed; break;
            case SDLK_LEFT: pos.x -= speed; break;
            default: break;
        }

        // 2 => Snap if collision
        LevelRect playerRect = getRect(pos, playerSize);
        for (const Item* item : *(game->getMap()->getItems())) if (item->type != GROUND) {
            LevelRect itemRect = getRect(item->pos, itemSize);
            if (!playerRect.intersect(itemRect)) continue;

            switch (playerRect.getCollidedFace(itemRect)) {
                case NORTH: pos.y = item->pos.y - itemSize.h / 2.0f - playerSize.h / 2.0f; break;
                case EAST: pos.x = item->pos.x + itemSize.w / 2.0f + playerSize.w / 2.0f; break;
                case SOUTH: pos.y = item->pos.y + itemSize.h / 2.0f + playerSize.h / 2.0f; break;
                case WEST: pos.x = item->pos.x - itemSize.w / 2.0f - playerSize.w / 2.0f; break;
                default: break;
            }
        }

        // 3 => Camera
        LevelPos camPos = camera->getPos();
        if (camPos.x + camPadding > pos.x) camPos = { pos.x - camPadding, camPos.y };
        if (camPos.x + BLOCKS_ON_WIDTH - camPadding < pos.x) camPos = { pos.x + camPadding - BLOCKS_ON_WIDTH, camPos.y };
        if (camPos.y + camPadding > pos.y) camPos = { camPos.x, pos.y - camPadding };
        if (camPos.y + BLOCKS_ON_HEIGHT - camPadding < pos.y) camPos = { camPos.x, pos.y + camPadding - BLOCKS_ON_HEIGHT };
        camera->setPos(camPos);

        // 4 => Target
        H2DE_Pos mousePos = game->getMousePos();
        target = c->computePxPos(mousePos.x, mousePos.y);
    }
    weapon->update();
}

// RENDER
void Player::render() {
    if (dead) return;
    renderPlayer();
    weapon->render();
    renderHealthBar();
}

void Player::renderPlayer() {
    static H2DE_Engine* engine = game->getEngine();
    static Camera* camera = game->getCamera();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();

    static H2DE_Size size = c->convertToPx(gameData->sizes->player);

    if (camera->contains(getRect(pos, gameData->sizes->player))) {
        H2DE_GraphicObject* player = H2DE_CreateGraphicObject();
        player->type = POLYGON;
        player->pos = c->convertToPx(pos, gameData->sizes->player);
        player->points = {
            { 0, 0 },
            { size.w, 0 },
            { size.w, size.h },
            { 0, size.h },
        };
        player->rgb = { 0, 255, 0, 255 };
        player->filled = true;
        player->index = 10;
        H2DE_AddGraphicObject(engine, player);
    }
}

void Player::renderHealthBar() {
    if (!renderHealthBarBG()) return;
    renderHealthBarPoints({ 0, 255, 0, 255 });
}

// EVENTS
void Player::kill() {

}

// GETTER
LevelSize Player::getSize() {
    static GameData* gameData = game->getData();
    return gameData->sizes->player;
}

// SETTER
void Player::setShooting(bool value) {
    weapon->setShooting(value);
}

void Player::setWeapon(Weapon* w) {
    weapon = w;
}



// ENEMY
// INIT
Enemy::Enemy(Game* g, EntityData d) : Entity(g, d) {

}
// CLEANUP
Enemy::~Enemy() {
    game->getMap()->destroyEntity(this);
}

// UPDATE
void Enemy::update() {
    if (!dead) target = game->getMap()->getPlayer()->getPos();
    weapon->update();
    if (weapon->areShotsFinished()) delete this;
}

// RENDER
void Enemy::render() {
    if (!dead) {
        renderEnemy();
        renderHealthBar();
    }
    weapon->render();
}

void Enemy::renderEnemy() {
    static H2DE_Engine* engine = game->getEngine();
    static Camera* camera = game->getCamera();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();

    static int size = c->convertToPx(gameData->sizes->enemy).w;

    if (camera->contains(getRect(pos, gameData->sizes->enemy))) {
        H2DE_GraphicObject* a = H2DE_CreateGraphicObject();
        a->type = POLYGON;
        a->pos = c->convertToPx(pos, gameData->sizes->enemy);
            a->points = {
            { 0, 0 },
            { size, 0 },
            { size, size },
            { 0, size },
        };
        a->rgb = { 255, 0, 0, 255 };
        a->filled = true;
        a->index = 11;
        H2DE_AddGraphicObject(engine, a);
    }
}

void Enemy::renderHealthBar() {
    if (!renderHealthBarBG()) return;
    renderHealthBarPoints({ 255, 0, 0, 255 });
}

// EVENTS
void Enemy::kill() {
    dead = true;
    weapon->setShooting(false);
}

// GETTER
LevelSize Enemy::getSize() {
    static GameData* gameData = game->getData();
    return gameData->sizes->enemy;
}

// SETTER
void Enemy::setWeapon(Weapon* w) {
    weapon = w;
    weapon->setShooting(true);
}



// ENTITY CASTER
Player* EntityCaster::castToPlayer(Entity* entity) {
    return dynamic_cast<Player*>(entity);
}

Enemy* EntityCaster::castToEnemy(Entity* entity) {
    return dynamic_cast<Enemy*>(entity);
}
