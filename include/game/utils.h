#ifndef UTILS_H
#define UTILS_H

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
};

struct Rotation {
    float x, y;
};

struct Translate {
    float x, y;
};

struct Scale {
    float x, y;
};

struct Transform {
    Rotation rotation;
    Translate translate;
    Scale scale;
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
    Transform tranform;
};

struct Item {
    ItemType type;
    LevelPos pos;

    LevelRect getRect() { return { pos.x - 0.5f, pos.y -0.5f, 1.0f, 1.0f }; }
};

#endif
