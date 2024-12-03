#ifndef GAME_H
#define GAME_H

#include <H2DE/H2DE.h>
#include "utils.h"
#include "data.h"
#include "functions.h"
#include "calculator.h"
#include "map.h"
#include "camera.h"
class Calculator;
class Map;
class Camera;

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    H2DE_Engine* engine;
    unsigned int FPS;
    bool isRunning = true;

    std::unordered_map<SDL_Keycode, bool> keyPressed;

    Calculator* calculator = nullptr;
    Camera* camera = nullptr;
    Map* map = nullptr;
    GameState state = PLAYING;

    void createWindow();

public:
    Game(unsigned int fps);
    ~Game();

    void run();
    void quit();
    void handleEvents(SDL_Event event);
    void update();
    void render();

    H2DE_Engine* getEngine();
    Calculator* getCalculator();
    Camera* getCamera();
    GameState getState();
    std::vector<SDL_Keycode> getPressedKeys();
};

#endif
