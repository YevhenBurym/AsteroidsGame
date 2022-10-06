//
// Created by Евгений on 22.07.2022.
//

#include "GameOverState.h"

GameOverState::GameOverState(GameWindow *gameWindow) {
    this->gameWindow = gameWindow;

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

    int hMenu,wMenu;
    int hRestart,wRestart;
    int hGameOver,wGameOver;
    this->gameWindow->getTextureManager()->getTextureSize("game_over", wGameOver, hGameOver);
    this->gameWindow->getTextureManager()->getTextureSize("menu_button", wMenu, hMenu);
    this->gameWindow->getTextureManager()->getTextureSize("restart_button", wRestart, hRestart);

    double xGameOver = this->gameWindow->getSize().width / 2 - wGameOver / 4;
    double yGameOver = this->gameWindow->getSize().height / 5 - hGameOver / 2;


    double xMenu = this->gameWindow->getSize().width / 2 - wMenu / 4;
    double yMenu = 2 * this->gameWindow->getSize().height / 5 - hMenu / 2;
    double xRestart = this->gameWindow->getSize().width / 2 - wRestart / 4;
    double yRestart = 3 * this->gameWindow->getSize().height / 5 - hRestart / 2;

    auto gameOverText = new GameOverMessage({xGameOver, yGameOver}, "game_over", this->gameWindow->getTextureManager(), 2);
    auto button1 = new Button({xMenu, yMenu}, "menu_button", this->gameWindow->getTextureManager(),
                              this->gameWindow->getInputHadler(), toMain);
    auto button2 = new Button({xRestart, yRestart}, "restart_button", this->gameWindow->getTextureManager(),
                              this->gameWindow->getInputHadler(), toRestart);
    this->gameOverObjects.push_back(gameOverText);
    this->gameOverObjects.push_back(button1);
    this->gameOverObjects.push_back(button2);

    SDL_ShowCursor(SDL_ENABLE);
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

std::string GameOverState::getStateID() const {
    return GameOverState::gameOverID;
}

GameOverState::~GameOverState() {
    for (auto &gameObject : this->gameOverObjects) {
        delete gameObject;
    }
    this->gameOverObjects.clear();
}
