#include "weapon.h"

// INIT
Weapon::Weapon(Game* g, WeaponData d) : game(g), data(d) {

}

// CLEANUP
Weapon::~Weapon() {
    
}

// UPDATE
void Weapon::update() {
    static Calculator* c = game->getCalculator();

    H2DE_Pos mousePos = game->getMousePos();
    if (shooting && SDL_GetTicks() - lastShot >= data.delay) {
        shot(c->computePxPos(mousePos.x, mousePos.y));
        lastShot = SDL_GetTicks();
    }

    for (Bullet* bullet : bullets) bullet->update();
}

// RENDER
void Weapon::render() {
    for (Bullet* bullet : bullets) bullet->render();
}

// EVENTS
void Weapon::shot(LevelPos pos) {
    static Player* player = game->getMap()->getPlayer();
    static float bulletRange = game->getData()->physics->bulletRange;

    LevelPos playerPos = player->getPos();
    double angle = std::atan2(pos.y - playerPos.y, pos.x - playerPos.x);

    for (BulletData bData : data.bullets) {
        LevelVelocity bulletVelocity = { static_cast<float>(std::cos(angle)) / 10.0f, static_cast<float>(std::sin(angle)) / 10.0f };
        bullets.push_back(new Bullet(game, bData, playerPos, bulletVelocity));
    }
}

void Weapon::destroyBullet(Bullet* bullet) {
    bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
}

// SETTER
void Weapon::setShooting(bool value) {
    shooting = value;
}
