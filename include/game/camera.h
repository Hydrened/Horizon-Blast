#ifndef CAMERA_H
#define CAMERA_H

#include "game.h"
class Game;

class Camera {
private:
    Game* game;

    LevelPos pos = { -9.5, 0 };

public:
    Camera(Game* game);
    ~Camera();

    LevelPos getPos();
    void setPos(LevelPos pos);
};

#endif
