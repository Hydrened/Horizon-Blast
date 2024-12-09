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
    EntityData data;
    Weapon* weapon = nullptr;

    LevelPos target;
    
    float health;
    LevelPos pos;
    bool dead = false;

    bool renderHealthBarBG();
    void renderHealthBarPoints(H2DE_RGB rgb);

public:
    Entity(Game* game, EntityData data);
    virtual ~Entity();

    virtual void update() = 0;
    virtual void render() = 0;
    
    void decreaseHealth(float damage);
    virtual void kill() = 0;
    void resetPos();

    LevelPos getPos() const;
    virtual LevelSize getSize() = 0;
    Weapon* getWeapon() const;
    LevelPos getTarget() const;
    bool isDead() const;

    virtual void setWeapon(Weapon* weapon) = 0;
};



class Player : public Entity {
private:
    void renderPlayer();
    void renderHealthBar();

public:
    Player(Game* game, EntityData data);
    ~Player() override;

    void update() override;
    void render() override;

    void kill() override;

    LevelSize getSize() override;

    void setShooting(bool value);
    void setWeapon(Weapon* weapon) override;
};



class Enemy : public Entity {
private:
    void renderEnemy();
    void renderHealthBar();

public:
    Enemy(Game* game, EntityData data);
    ~Enemy() override;

    void update() override;
    void render() override;
    
    void kill() override;
    
    LevelSize getSize() override;

    void setWeapon(Weapon* weapon) override;
};



class EntityCaster {
public:
    static Player* castToPlayer(Entity* entity);
    static Enemy* castToEnemy(Entity* entity);
};

#endif
