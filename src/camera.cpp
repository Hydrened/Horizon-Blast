#include "camera.h"

// INIT
Camera::Camera(Game* g) : game(g) {
    // static GameData* gameData = game->getData();
    
    // setPos(gameData->positions->camera, 0);
}

// CLEANUP
Camera::~Camera() {

}

// GETTER
LevelPos Camera::getPos() {
    return pos;
}

//SETTER
void Camera::setPos(LevelPos p) {
    pos = p;
}
