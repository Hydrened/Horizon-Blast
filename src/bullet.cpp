#include "bullet.h"

Bullet::Bullet(Game* g, BulletData d, LevelPos s, LevelPos e) : game(g), data(d), start(s), end(e), pos(s) {
    static GameData* gameData = game->getData();

    H2DE_AddTimelineToManager(tm, H2DE_CreateTimeline(g->getEngine(), static_cast<unsigned int>(gameData->physics->bulletDuration / data.speed), LINEAR, [this](float blend) {
        pos.x = lerp(start.x, end.x, blend);
        pos.y = lerp(start.y, end.y, blend);
    }, [this]() { delete this; }, 0));
}

Bullet::~Bullet() {
    static Weapon* weapon = game->getMap()->getPlayer()->getWeapon();
    weapon->destroyBullet(this);
    H2DE_DestroyTimelineManager(tm);
}

void Bullet::update() {
    H2DE_TickTimelineManager(tm);
}

void Bullet::render() {
    static H2DE_Engine* engine = game->getEngine();
    static Calculator* c = game->getCalculator();
    static GameData* gameData = game->getData();
    static H2DE_Size size = c->convertToPx(gameData->sizes->bullet);

    H2DE_GraphicObject* a = H2DE_CreateGraphicObject();
    a->type = POLYGON;
    a->pos = c->convertToPx(pos, gameData->sizes->bullet);
        a->points = {
        { 0, 0 },
        { size.w, 0 },
        { size.w, size.h },
        { 0, size.h },
    };
    a->rgb = { 0, 255, 0, 255 };
    a->filled = true;
    a->index = 9;
    H2DE_AddGraphicObject(engine, a);
}
