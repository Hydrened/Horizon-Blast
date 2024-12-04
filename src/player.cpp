#include "player.h"

// INIT
Player::Player(Game* g, Map* m) : game(g), map(m) {
    static GameData* gameData = game->getData();
    pos = gameData->positions->player;
}

// CLEANUP
Player::~Player() {

}

// UPDATE
void Player::update() {
    static Camera* camera = game->getCamera();
    static GameData* gameData = game->getData();

    static float BLOCKS_ON_HEIGHT = BLOCKS_ON_WIDTH * 9 / 16;
    static float speed = gameData->physics->playerSpeed;
    static float camPadding = gameData->sizes->cameraPadding;
    static LevelSize itemSize = { 1.0f, 1.0f };

    if (game->getState() != PLAYING) return;

    // 1 => Movements
    std::vector<Item*>* items = game->getMap()->getItems();
    for (const SDL_Keycode key : game->getPressedKeys()) {
        switch (key) {
            case SDLK_UP: pos.y += speed; break;
            case SDLK_RIGHT: pos.x += speed; break;
            case SDLK_DOWN: pos.y -= speed; break;
            case SDLK_LEFT: pos.x -= speed; break;
            default: break;
        }
    }

    // 2 => Camera
    LevelPos camPos = camera->getPos();
    if (camPos.x + camPadding > pos.x) camPos = { pos.x - camPadding, camPos.y };
    if (camPos.x + BLOCKS_ON_WIDTH - camPadding < pos.x) camPos = { pos.x + camPadding - BLOCKS_ON_WIDTH, camPos.y };
    if (camPos.y + camPadding > pos.y) camPos = { camPos.x, pos.y - camPadding };
    if (camPos.y + BLOCKS_ON_HEIGHT - camPadding < pos.y) camPos = { camPos.x, pos.y + camPadding - BLOCKS_ON_HEIGHT };
    camera->setPos(camPos);

    // 3 => Bullets
    for (Bullet* bullet : bullets) bullet->update();
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
    a->rgb = { 255, 0, 0, 255 };
    a->filled = true;
    a->index = 10;
    H2DE_AddGraphicObject(engine, a);

    for (Bullet* bullet : bullets) bullet->render();
}

// EVENTS
void Player::shot(LevelPos p) {
    static H2DE_Engine* engine = game->getEngine();
    static float bulletRange = game->getData()->physics->bulletRange;

    double angle = std::atan2(p.y - pos.y, p.x - pos.x);
    LevelPos start = pos;
    LevelPos end = { pos.x + bulletRange * static_cast<float>(std::cos(angle)), pos.y + bulletRange * static_cast<float>(std::sin(angle)) };

    BulletData bulletData = BulletData();
    bulletData.speed = 1.2f;

    bullets.push_back(new Bullet(game, start, end, bulletData));
}

//GETTER
std::vector<Bullet*>* Player::getBullets() {
    return &bullets;
}
