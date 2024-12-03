#include "player.h"

// INIT
Player::Player(Game* g, Map* m) : game(g), map(m) {

}

// CLEANUP
Player::~Player() {
    
}

// UPDATE
void Player::update() {
    if (game->getState() != PLAYING) return;

    for (const SDL_Keycode key : game->getPressedKeys()) switch (key) {
        case SDLK_UP: pos.y += 0.1; break;
        case SDLK_RIGHT: pos.x += 0.1; break;
        case SDLK_DOWN: pos.y -= 0.1; break;
        case SDLK_LEFT: pos.x -= 0.1; break;
        default: break;
    }
}

// RENDER
void Player::render() {
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();

    static int size = c->convertToPx({ 1, 1 }).w;

    H2DE_GraphicObject* a = H2DE_CreateGraphicObject();
    a->type = POLYGON;
    a->pos = c->convertToPx(pos, { 1, 1 });
        a->points = {
        { 0, 0 },
        { size, 0 },
        { size, size },
        { 0, size },
    };
    a->rgb = { 255, 0, 0, 255 };
    a->filled = true;
    a->index = 1;
    H2DE_AddGraphicObject(engine, a);
}

// EVENTS
void Player::shot(LevelPos pos) {
    std::cout << pos.x << " " << pos.y << std::endl;
}
