//
// Created by Евгений on 04.07.2022.
//

#include "Game.h"

Game::Game(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability) {
    if (wMap < wScreen) {
        wMap = wScreen;
    }
    if (hMap < hScreen) {
        hMap = wScreen;
    }
    this->hMap = hMap;
    this->wMap = wMap;
    this->asteroidsLimit = asteroidsLimit;
    this->ammoLimit = ammoLimit;
    this->numBullets = 0;
    this->numAsteroids = 0;

    this->gameWindow = new Window("Asteroids", wScreen, hScreen, false, false);

}

bool Game::init() {
    this->collisions = new Collisions(this);
    this->map = new Map(this->wMap, this->hMap, this->gameWindow);
    this->unitManager = new UnitManager(this);
    this->unitManager->createAvatar();
    return true;
}

void Game::close() {
    this->numBullets = 0;
    this->numAsteroids = 0;
    delete this->map;
    delete this->collisions;
    delete this->unitManager;
}

bool Game::tick() {
    this->map->draw();
    this->unitManager->createAsteroids();
    this->collisions->check();
    this->unitManager->deAcceleration();
    this->unitManager->calcOffset();
    this->unitManager->getAvatar()->shipHeadAngle();
    this->unitManager->drawAsteroids();
    this->unitManager->getAvatar()->getReticle()->draw();

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

        //Clear screen
        //SDL_RenderClear( this->gameWindow->getRenderer() );
//----------------ShownCursor----------------------------------------//

//        while ( lag >= stepMS ) {
//            this->tick();
//            lag -= stepMS;
//        }
//-------------------Tick-------------------------------------------//
        this->tick();
//------------------------------------------------------------------//
        this->gameWindow->updateWindow();
        SDL_Delay(1);
    }

//-----------------Close--------------------------------------------//
    this->close();
//------------------------------------------------------------------//
    //Destroy window
    delete this->inputHandler;
    delete this->gameWindow;
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

int Game::getNumBullets() const {
    return this->numBullets;
}

int Game::getNumAsteroids() const {
    return this->numAsteroids;
}

void Game::setNumBullets(int amount) {
    this->numBullets = amount;
}

void Game::setNumAsteroids(int amount) {
    this->numAsteroids = amount;
}
