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
    this->numAsteroids = 0;

    this->gameWindow = new Window("Asteroids", wScreen, hScreen, false, false);
    this->map = new Map(this->wMap, this->hMap, this->gameWindow);
}

void Game::createAvatar() {
    CoordXY avatarCoord;
    avatarCoord.x = this->map->getWMap()/2 - this->map->getMapOffsetCoord().x;
    avatarCoord.y = this->map->getHMap()/2 - this->map->getMapOffsetCoord().y;
    this->avatar = new Avatar(avatarCoord, 0, 0, this->map->getUnitSprites().spaceshipSprite, this->getAmmoLimit(), this->map);
    this->gameObjects.push_back(this->avatar);
}

bool Game::init() {
    this->collisions = new Collisions(this);
    this->createAvatar();
    this->unitManager = new UnitManager(this);
    return true;
}

void Game::close() {
    this->numAsteroids = 0;
    this->map->mapInit();
    delete this->collisions;
    delete this->unitManager;

    for (auto it = this->gameObjects.begin(); it != this->gameObjects.end(); ) {
        delete (*it++);
    }
    this->gameObjects.clear();
    this->gameObjects.shrink_to_fit();
}

bool Game::tick() {
    this->map->draw();
    this->unitManager->createAsteroids();
    this->collisions->check();
    this->unitManager->deAcceleration();
    this->unitManager->calcObjectOffset();
    this->avatar->shipHeadAngle();
    this->unitManager->drawAsteroids();
    this->avatar->getReticle()->draw();

    return false;
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

    bool quit = false;

//    double previous = this->getWindow()->getTickCounting();
//    double lag = 0.0;
//    double stepMS = 16;
    //Event handler
    SDL_Event event;
    this->inputHandler = new InputComponent(this);
//------------------------init--------------------------------------//
    this->init();
//------------------------------------------------------------------//
    //While application is running
    while( !quit ) {
//        double current = this->getWindow()->getTickCounting();
//        double elapsed = current - previous;
//        previous = current;
//        lag += elapsed;

        //Handle events on queue
        while( SDL_PollEvent( &event ) != 0 ) {
            //User requests quit
            if( event.type == SDL_QUIT ) {
                quit = true;
            }
            this->inputHandler->handleInput(event);
        }
//        while ( lag >= stepMS ) {
//            this->tick();
//            lag -= stepMS;
//        }
        this->tick();
        this->gameWindow->updateWindow();
        SDL_Delay(1);
    }
    this->close();
}

UnitManager* Game::getUnitManager() const {
    return this->unitManager;
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

int Game::getNumAsteroids() const {
    return this->numAsteroids;
}

void Game::setNumAsteroids(int amount) {
    this->numAsteroids = amount;
}

Avatar* Game::getAvatar() const {
    return this->avatar;
}

Game::~Game() {
    delete this->inputHandler;
    delete this->gameWindow;
    delete this->map;
}
