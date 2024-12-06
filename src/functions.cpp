#include "functions.h"

float lerp(float min, float max, float blend) {
    return min + blend * (max - min);
}

LevelRect getRect(LevelPos pos, LevelSize size) {
    return { pos.x, pos.y, size.w, size.h };
}
