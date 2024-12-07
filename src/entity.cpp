#include "entity.h"

// ENTITY
// INIT
Entity::Entity(Game* g, LevelPos p) : game(g), pos(p) {

}

// CLEANUP
Entity::~Entity() {
    delete weapon;
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
Player::Player(Game* g, LevelPos p) : Entity(g, p) {

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

    if (game->getState() != PLAYING) return;

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

    // 4 => Weapon
    H2DE_Pos mousePos = game->getMousePos();
    target = c->computePxPos(mousePos.x, mousePos.y);
    weapon->update();
}

// RENDER
void Player::render() {
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();

    static int size = c->convertToPx(gameData->sizes->player).w;

    H2DE_GraphicObject* a = H2DE_CreateGraphicObject();
    a->type = POLYGON;
    a->pos = c->convertToPx(pos, gameData->sizes->player);
        a->points = {
        { 0, 0 },
        { size, 0 },
        { size, size },
        { 0, size },
    };
    a->rgb = { 0, 255, 0, 255 };
    a->filled = true;
    a->index = 10;
    H2DE_AddGraphicObject(engine, a);

    weapon->render();
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
Enemy::Enemy(Game* g, LevelPos p) : Entity(g, p) {
    
}

// CLEANUP
Enemy::~Enemy() {

}

// UPDATE
void Enemy::update() {
    target = game->getMap()->getPlayer()->getPos();
    weapon->update();
}

// RENDER
void Enemy::render() {
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();

    static int size = c->convertToPx(gameData->sizes->enemy).w;

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

    weapon->render();
}

// SETTER
void Enemy::setWeapon(Weapon* w) {
    weapon = w;
    weapon->setShooting(true);
}
