#include "game.h"

// INIT
Game::Game(unsigned int f) : FPS(f) {
    createWindow();
    H2DE_LoadAssets(engine, "assets");
    
    calculator = new Calculator(this);
    camera = new Camera(this);
    map = new Map(this);
}

void Game::createWindow() {
    int x = 100;
    int y = 100;
    int w = 1280;
    int h = 720;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("HS-101: Error creating window => SDL_Init failed: " + std::string(SDL_GetError()));
    }

    window = SDL_CreateWindow("Hydren Shooter 1.0.0", x, y, w, h, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        throw std::runtime_error("HS-102: Error creating window => SDL_CreateWindow failed: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("HS-103: Error creating window => SDL_CreateRenderer failed: " + std::string(SDL_GetError()));
    }

    engine = H2DE_CreateEngine(renderer, w, h, FPS);
    if (!engine) {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        throw std::runtime_error("HS-104: Error creating window => H2DE_CreateEngine failed");
    }

    SDL_SetWindowMaximumSize(window, w, h);
    H2DE_SetEngineMaximumSize(engine, w, h);
}

// CLEANUP
Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    H2DE_DestroyEngine(engine);
    SDL_Quit();
}

void Game::quit() {
    isRunning = false;
}

// RUN
void Game::run() {
    Uint32 now, fpsTimer = SDL_GetTicks();
    int frameTime;
    SDL_Event event;

    while (isRunning) {
        int timePerFrame = 1000 / FPS;
        now = SDL_GetTicks();

        handleEvents(event);
        update();
        render();
        H2DE_RenderEngine(engine);
        
        frameTime = SDL_GetTicks() - now;
        if (timePerFrame >= frameTime) SDL_Delay(timePerFrame - frameTime);
    }
}

// EVENTS
void Game::handleEvents(SDL_Event event) {
    static Player* player = map->getPlayer();

    while (SDL_PollEvent(&event)) switch (event.type) {
        case SDL_QUIT: quit(); break;
        case SDL_KEYDOWN: keyPressed[event.key.keysym.sym] = true; break;
        case SDL_KEYUP: keyPressed[event.key.keysym.sym] = false; break;
        case SDL_MOUSEBUTTONDOWN: if (event.button.button == SDL_BUTTON_LEFT) switch (state) {
            case PLAYING: player->shot(calculator->convertToLevelPos(event.button.x, event.button.y, { 10, 10 })); break;
            default: break;
        } break;
        default: break;
    }
}

// UPDATE
void Game::update() {
    map->update();
}

// RENDER
void Game::render() {
    map->render();
}

// GETTER
H2DE_Engine* Game::getEngine() {
    return engine;
}

Calculator* Game::getCalculator() {
    return calculator;
}

Camera* Game::getCamera() {
    return camera;
}

GameState Game::getState() {
    return state;
}

std::vector<SDL_Keycode> Game::getPressedKeys() {
    std::vector<SDL_Keycode> res;
    for (const auto& [key, value] : keyPressed) if (value) res.push_back(key);
    return res;
}
