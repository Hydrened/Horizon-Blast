#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <vector>
class Bullet;

enum GameState {
    MENU,
    PLAYING,
    PAUSE,
    DEAD,
};

enum ItemType {
    GROUND = 0,
    WALL = 1,
    HOLE = 2,
};

enum Face {
    NORTH,
    EAST,
    SOUTH,
    WEST,
};

enum Team {
    PLAYER,
    ENEMY,
};

struct LevelOffset {
    float x, y;
};

struct LevelPos {
    float x, y;

    LevelPos operator +(const LevelOffset offset) const;
    LevelPos operator -(const LevelOffset offset) const;
};

struct LevelSize {
    float w, h;
};

struct LevelVelocity {
    float x, y;
};

struct LevelRect {
    float x, y, w, h;

    bool intersect(LevelPos pos) const;
    bool intersect(LevelRect rect) const;
    bool intersect(LevelRect rect, LevelVelocity velocity) const;
    Face getCollidedFace(LevelRect rect) const;
    Face getCollidedFace(LevelRect rect, LevelVelocity velocity) const;
};

struct LevelData {
    unsigned int id;
};

struct BulletData {
    Team canDamage;
    float speed = 1.0f;
    float damage = 1.0f;
    unsigned int rebound = 0;
    bool pierce = false;
    bool explosive = false;
    float angle = 0.0f;
};

struct WeaponData {
    unsigned int delay;
    std::vector<BulletData> bullets;
};

struct EntityData {
    float health;
    LevelPos pos;
};

struct Item {
    ItemType type;
    LevelPos pos;
};

#endif
