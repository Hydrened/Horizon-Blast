#include "weapon.h"

// INIT
Weapon::Weapon(Game* g, Entity* o, WeaponData d) : game(g), owner(o), data(d) {

}

// CLEANUP
Weapon::~Weapon() {
    
}

// UPDATE
void Weapon::update() {
    if (game->getState() == PLAYING) {
        if (shooting && delayFrameCount >= game->getNbStep(data.delay)) {
            shot(owner->getTarget());
            delayFrameCount = 0;
        }

        for (Bullet* bullet : bullets) bullet->update();
        delayFrameCount++;
    }
}

// RENDER
void Weapon::render() {
    for (Bullet* bullet : bullets) bullet->render();
}

// EVENTS
void Weapon::reset() {
    shooting = false;
    delayFrameCount = UINT_MAX;

    for (Bullet* bullet : bullets) destroyBullet(bullet);
    bullets.clear();
}

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

// GETTER
bool Weapon::areShotsFinished() const {
    return bullets.size() == 0;
}

// SETTER
void Weapon::setShooting(bool value) {
    shooting = value;
}
