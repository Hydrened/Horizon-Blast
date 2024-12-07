#ifndef CAMERA_H
#define CAMERA_H

#include "game.h"
class Game;

class Camera {
private:
    Game* game;

    LevelPos pos;

public:
    Camera(Game* game);
    ~Camera();

    bool contains(LevelRect element);

    LevelPos getPos() const;
    void setPos(LevelPos pos);
};

#endif
