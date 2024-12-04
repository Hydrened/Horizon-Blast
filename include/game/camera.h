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

    void update();

    LevelPos getPos();
    void setPos(LevelPos pos);
};

#endif
