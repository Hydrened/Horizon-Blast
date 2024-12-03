#include "calculator.h"

// INIT
Calculator::Calculator(Game* g) : game(g) {

}

// CLEANUP
Calculator::~Calculator() {

}

// CONVERT TO PX
H2DE_Pos Calculator::convertToPx(LevelPos p, LevelSize s) {
    H2DE_Size engineSize;
    int blockSize;
    getUtils(&engineSize, &blockSize);
    LevelPos c = game->getCamera()->getPos();

    return {
        (int)((p.x - c.x) * blockSize),
        (int)(engineSize.h - (p.y - c.y + s.h) * blockSize)
    };
}

H2DE_Size Calculator::convertToPx(LevelSize s) {
    H2DE_Size engineSize;
    int blockSize;
    getUtils(&engineSize, &blockSize);

    return {
        (int)(s.w * blockSize),
        (int)(s.h * blockSize)
    };
}

// CONVERT TO LEVEL
LevelPos Calculator::convertToLevelPos(int x, int y, LevelSize s) {
    H2DE_Size engineSize;
    int blockSize;
    getUtils(&engineSize, &blockSize);
    LevelPos c = game->getCamera()->getPos();

    return {
        (float)x / blockSize + c.x,
        (float)(engineSize.h - y) / blockSize + c.y - s.h
    };
}

// GETTER
void Calculator::getUtils(H2DE_Size* engineSize, int* blockSize) {
    *engineSize = H2DE_GetEngineSize(game->getEngine());
    *blockSize = engineSize->w / BLOCKS_ON_WIDTH;
}
