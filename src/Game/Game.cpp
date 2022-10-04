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
    this->gameWindow = new GameWindow("Asteroids", wScreen, hScreen, false);
    this->map = new Map(this->wMap, this->hMap, this->gameWindow);
}

bool Game::init() {
    //this->map->mapInit();
    //this->objectManager = new ObjectManager(this->gameWindow, this->map, this->asteroidsLimit, this->ammoLimit);
    //this->collisions = new Collisions(this->objectManager);
    this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow));
    return true;
}

void Game::update() {
    this->gameWindow->getInputHadler()->update();
//    if (this->gameWindow->getInputHadler()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
//        this->gameWindow->setFlagQuitGame(true);
//    }
//    this->map->update();
//    this->objectManager->update();
//    try {
//        this->collisions->update();
//    } catch (YouDied) {
//        this->restart();
//    }
    this->gameWindow->getGameStateMachine()->update();
}

void Game::render() {
    SDL_RenderClear(this->gameWindow->getRenderer());

    //this->map->render();
    //this->objectManager->render();
    this->gameWindow->getGameStateMachine()->render();
    //SDL_ShowCursor(SDL_DISABLE);
    SDL_RenderPresent(this->gameWindow->getRenderer());
}

void Game::run() {
    const int fps = 60;
    const int frameDelay = 1000 / fps;
    Uint32 startTime;
    Uint32 frameTime;

    this->init();

    //While application is running
    while (!this->gameWindow->getFlagQuitGame() &&
    !this->gameWindow->getInputHadler()->getFlagQuitGame()) {
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
}

Game::~Game() {
    delete this->gameWindow;
    delete this->map;
}

void Game::close() {
    //delete this->collisions;
    //delete this->objectManager;
}

void Game::restart() {
    this->close();
    this->init();
}


