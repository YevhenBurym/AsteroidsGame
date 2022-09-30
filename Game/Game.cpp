//
// Created by Евгений on 04.07.2022.
//

#include "Game.h"

Game::Game(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability) {
//    if (wMap < wScreen) {
//        wMap = wScreen;
//    }
//    if (hMap < hScreen) {
//        hMap = wScreen;
//    }
    this->hMap = hMap;
    this->wMap = wMap;
    this->asteroidsLimit = asteroidsLimit;
    this->ammoLimit = ammoLimit;
    this->quit = false;
    //this->initWindow("Asteroids", wScreen, hScreen, false);
    this->gameWindow = new Window("Asteroids", wScreen, hScreen, false);
    this->map = new Map(this->wMap, this->hMap, this->gameWindow);
}

void Game::loadSprites() {
    this->spriteManager->load("data\\back.png", "background");
    this->spriteManager->load("data\\border.png", "border");
    this->spriteManager->load("data\\ship.png", "spaceship");
    this->spriteManager->load("data\\small.png", "small_asteroid");
    this->spriteManager->load("data\\big.png", "big_asteroid");
    this->spriteManager->load("data\\reticle.png", "reticle");
    this->spriteManager->load("data\\bullet.png", "bullet");
}

void Game::createPlayer() {
    Vector2D avatarCoord{0, 0};
    avatarCoord.setX(this->map->getWMap() / 2 - this->map->getMapOffsetCoord().getX());
    avatarCoord.setY(this->map->getHMap() / 2 - this->map->getMapOffsetCoord().getY());
    this->ship = new SpaceShip(avatarCoord, 0, 0, this->map->getUnitSprites().spaceshipSprite, this->getAmmoLimit(),
                               this->map);
    this->gameObjects.push_back(this->ship);
}

bool Game::init() {
    this->spriteManager = new SpriteManager(this->gameWindow->getRenderer());
    this->loadSprites();
    this->inputHandler = new InputComponent(this);
    this->map->mapInit();
    this->collisions = new Collisions(this);
    this->createPlayer();
    this->asterManager = new AsteroidsManager(this);
    return true;
}

void Game::close() {

    delete this->collisions;
    delete this->asterManager;
    delete this->inputHandler;
    delete this->spriteManager;

    for (auto it = this->gameObjects.begin(); it != this->gameObjects.end();) {
        delete (*it++);
    }
    this->gameObjects.clear();
    this->gameObjects.shrink_to_fit();
}

void Game::handleEvents() {

}


void Game::update() {
    this->asterManager->createAsteroids();
    this->collisions->check();
    this->map->deAcceleration();
    this->calcObjectOffset();
    this->ship->shipHeadAngle();
}

void Game::render() {
    SDL_RenderClear(this->gameWindow->getRenderer());

    this->map->draw();
    this->renderObjects();
    SDL_ShowCursor(SDL_DISABLE);
    SDL_RenderPresent(this->gameWindow->getRenderer());
}

void Game::restart() {
    this->close();
    this->init();
}

Map *Game::getMap() const {
    return this->map;
}

Window *Game::getWindow() const {
    return this->gameWindow;
}

void Game::runGame() {
    const int fps = 60;
    const int frameDelay = 1000 / fps;
    Uint32 startTime;
    Uint32 frameTime;

    this->init();

    //While application is running
    while (!this->quit) {

        this->inputHandler->update();

        startTime = SDL_GetTicks();
        this->update();
        this->render();

        frameTime = SDL_GetTicks() - startTime;
//        if (frameDelay > frameTime) {
//            //std::cout <<frameDelay - frameTime << std::endl;
//            SDL_Delay(frameDelay - frameTime);
//
//        }
        SDL_Delay(1);
    }
    this->close();
    this->clean();
}

int Game::getAmmoLimit() const {
    return this->ammoLimit;
}

int Game::getAsteroidslimit() const {
    return this->asteroidsLimit;
}

std::vector<GameObject *> &Game::getObjects() {
    return this->gameObjects;
}

SpaceShip *Game::getPlayer() const {
    return this->ship;
}

Game::~Game() {
    delete this->inputHandler;
    delete this->gameWindow;
    delete this->map;
}

void Game::renderObjects() {
    for (auto &object : this->gameObjects) {
        object->calcCoord(object->getVxy(), 0.001);
        object->render();
    }
    this->ship->getReticle()->render();
}

void Game::calcObjectOffset() {
    this->map->calcCoord(this->map->getVx(), this->map->getVy(), 0.5);

    if (this->map->getVx() != 0 || this->map->getVy() != 0) {
        for (auto &gameObject : this->gameObjects) {
            gameObject->setXof(this->map->getX());
            gameObject->setYof(this->map->getY());
        }
    }
}

AsteroidsManager *Game::getAsterManager() const {
    return this->asterManager;
}

bool Game::initWindow(const char *name, int width, int height, bool isFullscreen) {
    this->window = nullptr;
    this->renderer = nullptr;
    this->hWindow = 0;
    this->wWindow = 0;
    bool isCreate;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize! SDL Error: %s" << SDL_GetError() << std::endl;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        Uint32 windowFlags = SDL_WINDOW_SHOWN;
        if (isFullscreen) {
            windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        this->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                        windowFlags);
        if (this->window == nullptr) {
            std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
        } else {
            //windowSize
            SDL_GetWindowSize(this->window, &this->wWindow, &this->hWindow);
            //Create vsynced renderer for window
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
            if (this->renderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
                } else {
                    isCreate = true;
                }
            }
        }
    }
    return isCreate;
}

SDL_Renderer *Game::getRenderer() const {
    return this->renderer;
}

void Game::clean() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    this->renderer = nullptr;
    this->window = nullptr;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void Game::setQuit(bool quit) {
    this->quit = quit;
}

