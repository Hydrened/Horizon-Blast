#ifndef UTILS_H
#define UTILS_H

enum GameState {
    MENU,
    PLAYING,
    PAUSE,
};

struct LevelPos {
    float x, y;
};

struct LevelSize {
    float w, h;
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

struct KeyEvent {
    SDL_KeyCode keycode;
    GameState state;
    std::function<void()> call;
};

#endif
