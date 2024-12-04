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
        (int)((p.x - c.x - s.w / 2) * blockSize),
        (int)(engineSize.h - (p.y - c.y + s.h / 2) * blockSize)
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

// COMPUTE
LevelPos Calculator::computePxPos(int x, int y) {
    H2DE_Size engineSize;
    int blockSize;
    getUtils(&engineSize, &blockSize);
    LevelPos c = game->getCamera()->getPos();

    return {
        (float)x / blockSize + c.x,
        (float)(engineSize.h - y) / blockSize + c.y
    };
}

// GETTER
void Calculator::getUtils(H2DE_Size* engineSize, int* blockSize) {
    *engineSize = H2DE_GetEngineSize(game->getEngine());
    *blockSize = engineSize->w / BLOCKS_ON_WIDTH;
}
