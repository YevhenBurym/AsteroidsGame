//
// Created by Евгений on 04.07.2022.
//

#include "Game.h"

Game::Game(GameParameters* parameters) {
    this->gameWindow = new GameWindow(parameters);
}

bool Game::init() {
    //this->gameWindow->getGameStateMachine()->changeState(new PlayState(this->gameWindow));
    this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow));
    return true;
}

void Game::update() {
    this->gameWindow->getInputHadler()->update();
    this->gameWindow->getGameStateMachine()->update();
}

void Game::render() {
    SDL_RenderClear(this->gameWindow->getRenderer());

    this->gameWindow->getGameStateMachine()->render();

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
}

Game::~Game() {
    delete this->gameWindow;
}



