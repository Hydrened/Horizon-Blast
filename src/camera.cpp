#include "camera.h"

// INIT
Camera::Camera(Game* g) : game(g) {
    static GameData* gameData = game->getData();
    setPos(gameData->positions->camera);
}

// CLEANUP
Camera::~Camera() {

}

// OTHER
bool Camera::contains(LevelRect element) {
    LevelRect cameraRect = getRect(pos, { BLOCKS_ON_WIDTH, BLOCKS_ON_HEIGHT });
    return element.intersect(cameraRect);
}

// GETTER
LevelPos Camera::getPos() const {
    return pos;
}

// SETTER
void Camera::setPos(LevelPos p) {
    pos = p;
}
