#include "weapon.h"

// INIT
Weapon::Weapon(Game* g, Entity* o, WeaponData d) : game(g), owner(o), data(d) {

}

// CLEANUP
Weapon::~Weapon() {
    
}

// UPDATE
void Weapon::update() {
    if (shooting && SDL_GetTicks() - lastShot >= data.delay) {
        shot(owner->getTarget());
        lastShot = SDL_GetTicks();
    }

    for (Bullet* bullet : bullets) bullet->update();
}

// RENDER
void Weapon::render() {
    for (Bullet* bullet : bullets) bullet->render();
}

// EVENTS
void Weapon::shot(LevelPos target) {
    static float bulletRange = game->getData()->physics->bulletRange;

    LevelPos source = owner->getPos();
    float targetAngle = std::atan2(target.y - source.y, target.x - source.x) * 180.0f / M_PI;

    for (BulletData bData : data.bullets) {
        double angle = (targetAngle - bData.angle) * (M_PI / 180.0f);
        LevelVelocity bulletVelocity = { static_cast<float>(std::cos(angle)) / 10.0f, static_cast<float>(std::sin(angle)) / 10.0f };
        bullets.push_back(new Bullet(game, this, bData, source, bulletVelocity));
    }
}

void Weapon::destroyBullet(Bullet* bullet) {
    bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
}

// SETTER
void Weapon::setShooting(bool value) {
    shooting = value;
}
