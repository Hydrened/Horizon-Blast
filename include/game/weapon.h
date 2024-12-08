#ifndef WEAPON_H
#define WEAPON_H

#include "game.h"
#include "entity.h"
#include "bullet.h"
class Game;
class Entity;

class Weapon {
private:
    Game* game;
    Entity* owner;
    WeaponData data;

    bool shooting = false;
    unsigned int delayFrameCount = UINT_MAX;

    std::vector<Bullet*> bullets;

public:
    Weapon(Game* game, Entity* owner, WeaponData data);
    ~Weapon();

    void update();
    void render();

    void shot(LevelPos pos);
    void destroyBullet(Bullet* bullet);

    bool areShotsFinished() const;

    void setShooting(bool value);
};

#endif
