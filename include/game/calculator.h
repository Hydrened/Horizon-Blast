#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "game.h"
class Game;

class Calculator {
private:
    Game* game;

    void getUtils(H2DE_Size* enginSize, int* blockSize);
    
public:
    Calculator(Game* game);
    ~Calculator();

    H2DE_Pos convertToPx(LevelPos pos, LevelSize size);
    H2DE_Size convertToPx(LevelSize size);

    LevelPos convertToLevelPos(int x, int y, LevelSize size);
};

#endif
