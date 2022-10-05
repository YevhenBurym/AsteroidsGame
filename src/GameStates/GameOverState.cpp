//
// Created by Евгений on 22.07.2022.
//

#include "GameOverState.h"

GameOverState::GameOverState(GameWindow* gameWindow) {
    this->gameWindow = gameWindow;
}

const std::string GameOverState::gameOverID = "GAME_OVER";

void GameOverState::s_gameOverToMain() {
    this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow));
}

void GameOverState::s_restartPlay() {
    this->gameWindow->getGameStateMachine()->changeState(new PlayState(this->gameWindow));
}

void GameOverState::update() {
    for(int i = 0; i < this->gameOverObjects.size(); i++) {
        this->gameOverObjects[i]->update();
    }
//    for (auto &gameObject : this->gameOverObjects) {
//        gameObject->update();
//    }
}

void GameOverState::render() {
//    for (auto & gameObject : this->gameOverObjects) {
//        gameObject->render();
//    }
    for(int i = 0; i < this->gameOverObjects.size(); i++) {
        this->gameOverObjects[i]->render();
    }
}


bool GameOverState::onEnter() {
    SDL_ShowCursor(SDL_ENABLE);
    auto gameOverText = new GameOverMessage({220,150},"game_over",this->gameWindow->getTextureManager(),2);
    auto button1 = new Button({280,250},"menu_button",this->gameWindow->getTextureManager(),this->gameWindow->getInputHadler(), [this]() {s_gameOverToMain();});
    auto button2 = new Button({280,350},"restart_button",this->gameWindow->getTextureManager(),this->gameWindow->getInputHadler(), [this]() {s_restartPlay();});
    this->gameOverObjects.push_back(gameOverText);
    this->gameOverObjects.push_back(button1);
    this->gameOverObjects.push_back(button2);
    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::onExit()
{
    for(auto & gameObject : this->gameOverObjects)
    {
        delete gameObject;
    }
    this->gameOverObjects.clear();
    std::cout << "exiting GameOverState\n";
    return true;
}

std::string GameOverState::getStateID() const {
    return GameOverState::gameOverID;
}