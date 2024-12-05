#include "functions.h"

float lerp(float min, float max, float blend) {
    return min + blend * (max - min);
}

LevelRect getRect(LevelPos pos, LevelSize size) {
    float x = pos.x;
    float y = pos.y;
    float w = size.w;
    float h = size.h;

    return { x - w / 2, y - h / 2, w, h };
}
