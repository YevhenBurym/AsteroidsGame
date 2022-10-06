//
// Created by Евгений on 22.07.2022.
//

#include "GameOverState.h"

GameOverState::GameOverState(GameWindow *gameWindow) {
    this->gameWindow = gameWindow;
}

const std::string GameOverState::gameOverID = "GAME_OVER";

void GameOverState::update() {
    for (auto &gameOverObject : this->gameOverObjects) {
        gameOverObject->update();
        if (this->gameWindow->getGameStateMachine()->needToErasePrevState()) {
            return;
        };
    }
}

void GameOverState::render() {
    for (auto &gameOverObject : this->gameOverObjects) {
        gameOverObject->render();
    }
}

bool GameOverState::onEnter() {
    SDL_ShowCursor(SDL_ENABLE);
    std::function<void()> toMain{
            [this]() {
                this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow));
            }
    };
    std::function<void()> toRestart{
            [this]() {
                this->gameWindow->getGameStateMachine()->changeState(new PlayState(this->gameWindow));
            }
    };
    auto gameOverText = new GameOverMessage({220, 150}, "game_over", this->gameWindow->getTextureManager(), 2);
    auto button1 = new Button({280, 250}, "menu_button", this->gameWindow->getTextureManager(),
                              this->gameWindow->getInputHadler(), toMain);
    auto button2 = new Button({280, 350}, "restart_button", this->gameWindow->getTextureManager(),
                              this->gameWindow->getInputHadler(), toRestart);
    this->gameOverObjects.push_back(gameOverText);
    this->gameOverObjects.push_back(button1);
    this->gameOverObjects.push_back(button2);

    return true;
}

bool GameOverState::onExit() {
    return true;
}

std::string GameOverState::getStateID() const {
    return GameOverState::gameOverID;
}

GameOverState::~GameOverState() {
    for (auto &gameObject : this->gameOverObjects) {
        delete gameObject;
    }
    this->gameOverObjects.clear();
}
