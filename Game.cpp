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
    this->initWindow("Asteroids", wScreen, hScreen, false);
    this->gameWindow = new Window("Asteroids", wScreen, hScreen, false);
    this->map = new Map(this->wMap, this->hMap, this->gameWindow);
}

void Game::createPlayer() {
    Vector2D avatarCoord{0,0};
    avatarCoord.setX(this->map->getWMap()/2 - this->map->getMapOffsetCoord().getX());
    avatarCoord.setY(this->map->getHMap()/2 - this->map->getMapOffsetCoord().getY());
    this->ship = new SpaceShip(avatarCoord, 0, 0, this->map->getUnitSprites().spaceshipSprite, this->getAmmoLimit(), this->map);
    this->gameObjects.push_back(this->ship);
}

bool Game::init() {
    this->map->mapInit();
    this->collisions = new Collisions(this);
    this->createPlayer();
    this->asterManager = new AsteroidsManager(this);
    return true;
}

void Game::close() {

    delete this->collisions;
    delete this->asterManager;

    for (auto it = this->gameObjects.begin(); it != this->gameObjects.end(); ) {
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
    SDL_RenderClear(this->renderer);

    this->map->draw();
    this->renderObjects();
    this->gameWindow->showCursor(false);

    SDL_RenderPresent(this->renderer);
}

void Game::restart() {
    this->close();
    this->init();
}

Map* Game::getMap() const {
    return this->map;
}

Window *Game::getWindow() const {
    return this->gameWindow;
}

void Game::runGame() {
    const int fps = 1000;
    const int frameDelay = 1000 / fps;
    Uint32 startTime;
    int frameTime;

    this->init();

    //Event handler
    SDL_Event event;
    this->inputHandler = new InputComponent(this);
    //While application is running
    while( !this->quit ) {

        //Handle events on queue
        while( SDL_PollEvent( &event ) != 0 ) {
            //User requests quit
            if( event.type == SDL_QUIT )  {
                this->quit = true;
            }
            if( event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_ESCAPE) {
                this->quit = true;
            }
            this->inputHandler->handleInput(event);
        }

        startTime = this->getWindow()->getTickCounting();
        this->update();
        this->render();

        frameTime = this->getWindow()->getTickCounting() - startTime;
//        if (frameDelay > frameTime) {
//            //std::cout <<frameDelay - frameTime << std::endl;
//            SDL_Delay(frameDelay - frameTime);
//
//        }
        SDL_Delay(1);
    }
    this->close();
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

SpaceShip* Game::getPlayer() const {
    return this->ship;
}

Game::~Game() {
    delete this->inputHandler;
    delete this->gameWindow;
    delete this->map;
}

void Game::renderObjects() {
    for (auto & object : this->gameObjects) {
        object->calcCoord(object->getVxy(), 0.001);
        object->render();
    }
    this->ship->getReticle()->render();
}

void Game::calcObjectOffset() {
    this->map->calcCoord(this->map->getVx(), this->map->getVy(), 0.5);

    if (this->map->getVx() != 0 || this->map->getVy() != 0) {
        for (auto & gameObject : this->gameObjects) {
            gameObject->setXof(this->map->getX());
            gameObject->setYof(this->map->getY());
        }
    }
}

AsteroidsManager *Game::getAsterManager() const {
    return this->asterManager;
}

bool Game::initWindow(const char* name, int width, int height, bool isFullscreen) {
    this->window = nullptr;
    this->renderer = nullptr;
    this->hWindow = 0;
    this->wWindow = 0;
    bool isCreate;

    //Initialize SDL
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
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
        if( this->window == nullptr ) {
            std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
        } else {
            //windowSize
            SDL_GetWindowSize(this->window, &this->wWindow, &this->hWindow);
            //Create vsynced renderer for window
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED );
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

