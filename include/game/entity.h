#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "map.h"
#include "weapon.h"
class Game;
class Map;
class Weapon;

class Entity {
protected:
    Game* game;
    LevelPos pos;
    Weapon* weapon = nullptr;

    LevelPos target;

public:
    Entity(Game* game, LevelPos pos);
    virtual ~Entity();

    virtual void update() = 0;
    virtual void render() = 0;

    LevelPos getPos() const;
    Weapon* getWeapon() const;
    LevelPos getTarget() const;

    virtual void setWeapon(Weapon* weapon) = 0;
};

class Player : public Entity {
private:

public:
    Player(Game* g, LevelPos p);
    ~Player() override;

    void update() override;
    void render() override;

    void setShooting(bool value);
    void setWeapon(Weapon* weapon) override;
};

class Enemy : public Entity {
private:

public:
    Enemy(Game* g, LevelPos p);
    ~Enemy() override;

    void update() override;
    void render() override;

    void setWeapon(Weapon* weapon) override;
};

#endif
