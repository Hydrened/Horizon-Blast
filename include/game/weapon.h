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
    Uint32 lastShot = SDL_MIN_UINT32;

    std::vector<Bullet*> bullets;

public:
    Weapon(Game* game, Entity* owner, WeaponData data);
    ~Weapon();

    void update();
    void render();

    void shot(LevelPos pos);
    void destroyBullet(Bullet* bullet);

    void setShooting(bool value);
};

#endif
