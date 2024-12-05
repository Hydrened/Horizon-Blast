#ifndef WEAPON_H
#define WEAPON_H

#include "game.h"
#include "bullet.h"
class Game;

class Weapon {
private:
    Game* game;
    WeaponData data;

    bool shooting = false;
    Uint32 lastShot = SDL_MIN_UINT32;

    std::vector<Bullet*> bullets;

public:
    Weapon(Game* game, WeaponData data);
    ~Weapon();

    void update();
    void render();

    void shot(LevelPos pos);
    void destroyBullet(Bullet* bullet);

    void setShooting(bool value);
};

#endif
