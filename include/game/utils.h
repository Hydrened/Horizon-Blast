#ifndef UTILS_H
#define UTILS_H

class Bullet;

enum GameState {
    MENU,
    PLAYING,
    PAUSE,
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

struct LevelPos {
    float x, y;
};

struct LevelSize {
    float w, h;
};

struct LevelRect {
    float x, y, w, h;

    bool intersect(LevelPos pos) {
        float left = x - w / 2.0f;
        float right = x + w / 2.0f;
        float top = y - h / 2.0f;
        float bottom = y + h / 2.0f;

        return (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom);
    }

    bool intersect(LevelRect rect) {
        float leftA = x - w / 2.0f;
        float rightA = x + w / 2.0f;
        float topA = y - h / 2.0f;
        float bottomA = y + h / 2.0f;

        float leftB = rect.x - rect.w / 2.0f;
        float rightB = rect.x + rect.w / 2.0f;
        float topB = rect.y - rect.h / 2.0f;
        float bottomB = rect.y + rect.h / 2.0f;

        return !(leftA > rightB || rightA < leftB || topA > bottomB || bottomA < topB);
    }

    Face getCollidedFace(LevelRect rect) {
        float leftA = x - w / 2.0f;
        float rightA = x + w / 2.0f;
        float topA = y - h / 2.0f;
        float bottomA = y + h / 2.0f;

        float leftB = rect.x - rect.w / 2.0f;
        float rightB = rect.x + rect.w / 2.0f;
        float topB = rect.y - rect.h / 2.0f;
        float bottomB = rect.y + rect.h / 2.0f;

        float overlapLeft = rightA - leftB;
        float overlapRight = rightB - leftA;
        float overlapTop = bottomA - topB;
        float overlapBottom = bottomB - topA;

        if (overlapTop <= overlapBottom && overlapTop <= overlapLeft && overlapTop <= overlapRight) return NORTH;
        else if (overlapBottom <= overlapTop && overlapBottom <= overlapLeft && overlapBottom <= overlapRight) return SOUTH;
        else if (overlapLeft <= overlapRight && overlapLeft <= overlapTop && overlapLeft <= overlapBottom) return WEST;
        else return EAST;
    }
};

struct LevelData {
    unsigned int id;
};

struct BulletData {
    float speed = 1.0f;
    float damage = 1.0f;
    int rebound = 0;
    bool pierce = false;
    bool explosive = false;
};

struct WeaponData {
    unsigned int delay;
    std::vector<BulletData> bullets;
};

struct Item {
    ItemType type;
    LevelPos pos;
};

#endif
