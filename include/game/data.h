#ifndef DATA_H
#define DATA_H

#define BLOCKS_ON_WIDTH 20.0f
#define BLOCKS_ON_HEIGHT 11.25f

struct GameData {
    struct Positions {
        LevelPos camera = { -10.0f, -3.5f };
        LevelPos player = { 0.0f, 0.0f };
    };

    struct Sizes {
        LevelSize player = { 0.75f, 0.75f };
        LevelSize enemy = { 0.75f, 0.75f };
        LevelSize item = { 1.0f, 1.0f };
        LevelSize bullet = { 0.2f, 0.2f };
        LevelSize map = { 50.0f, 50.0f };
        LevelSize healthBar = { 1.0f, 0.2f };
        float cameraPadding = 3.0f;
    };

    struct Offsets {
        LevelOffset healthBar = { 0.0f, 0.7f };
    };

    struct Physics {
        float playerSpeed = 0.1f;
        float bulletRange = 100.0f;
        int bulletDuration = 7500;
    };
    
    ~GameData() {
        delete positions;
        delete sizes;
        delete offsets;
        delete physics;
    };

    Positions* positions = new Positions();
    Sizes* sizes = new Sizes();
    Offsets* offsets = new Offsets();
    Physics* physics = new Physics();
};

#endif
