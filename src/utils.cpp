#include "utils.h"

LevelPos LevelPos::operator +(const LevelOffset offset) const {
    return { x + offset.x, y + offset.y };
}

LevelPos LevelPos::operator -(const LevelOffset offset) const {
    return { x - offset.x, y - offset.y };
}

bool LevelRect::intersect(LevelPos pos) const {
    float left = x - w / 2.0f;
    float right = x + w / 2.0f;
    float top = y - h / 2.0f;
    float bottom = y + h / 2.0f;

    return (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom);
}

bool LevelRect::intersect(LevelRect rect) const {
    return intersect(rect, { 0.0f, 0.0f });
}

bool LevelRect::intersect(LevelRect rect, LevelVelocity velocity) const {
    float leftA = std::min(x - w / 2.0f, (x + velocity.x) - w / 2.0f);
    float rightA = std::max(x + w / 2.0f, (x + velocity.x) + w / 2.0f);
    float topA = std::min(y - h / 2.0f, (y + velocity.y) - h / 2.0f);
    float bottomA = std::max(y + h / 2.0f, (y + velocity.y) + h / 2.0f);

    float leftB = rect.x - rect.w / 2.0f;
    float rightB = rect.x + rect.w / 2.0f;
    float topB = rect.y - rect.h / 2.0f;
    float bottomB = rect.y + rect.h / 2.0f;

    return !(leftA > rightB || rightA < leftB || topA > bottomB || bottomA < topB);
}

Face LevelRect::getCollidedFace(LevelRect rect) const {
    return getCollidedFace(rect, { 0.0f, 0.0f });
}

Face LevelRect::getCollidedFace(LevelRect rect, LevelVelocity velocity) const {
    float leftA = std::min(x - w / 2.0f, (x + velocity.x) - w / 2.0f);
    float rightA = std::max(x + w / 2.0f, (x + velocity.x) + w / 2.0f);
    float topA = std::min(y - h / 2.0f, (y + velocity.y) - h / 2.0f);
    float bottomA = std::max(y + h / 2.0f, (y + velocity.y) + h / 2.0f);

    float leftB = rect.x - rect.w / 2.0f;
    float rightB = rect.x + rect.w / 2.0f;
    float topB = rect.y - rect.h / 2.0f;
    float bottomB = rect.y + rect.h / 2.0f;

    float overlapLeft = rightA - leftB;
    float overlapRight = rightB - leftA;
    float overlapTop = bottomA - topB;
    float overlapBottom = bottomB - topA;

    if (overlapTop <= overlapBottom && overlapTop <= overlapLeft && overlapTop <= overlapRight) return NORTH;
    else if (overlapBottom <= overlapTop && overlapBottom <= overlapLeft && overlapBottom <= overlapRight) return SOUTH;
    else if (overlapLeft <= overlapRight && overlapLeft <= overlapTop && overlapLeft <= overlapBottom) return WEST;
    else return EAST;
}
