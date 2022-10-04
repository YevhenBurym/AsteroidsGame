//
// Created by Евгений on 22.07.2022.
//

#include "GameOverState.h"

GameOverState::GameOverState(GameWindow* gameWindow, InputComponent* inputComponent) {
    this->gameWindow = gameWindow;
    this->inputComponent = inputComponent;
}

const std::string GameOverState::gameOverID = "GAME_OVER";

void GameOverState::s_gameOverToMain() {
    this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow, this->inputComponent));
}

void GameOverState::s_restartPlay() {
    this->gameWindow->getGameStateMachine()->changeState(new PlayState(this->gameWindow, this->inputComponent));
}

void GameOverState::update() {
    for (auto &gameObject : this->gameOverObjects) {
        gameObject->update();
    }
}

void GameOverState::render() {
    for (auto & button : this->gameOverObjects) {
        button->render();
    }
}


bool GameOverState::onEnter() {
    auto gameOverText = new GameOverMessage({165,100},"game_over",this->gameWindow->getTextureManager(),2);
    auto button1 = new Button({220,200},"main_button",this->gameWindow->getTextureManager(),this->inputComponent, [this]() {s_gameOverToMain();});
    auto button2 = new Button({220,300},"restart_button",this->gameWindow->getTextureManager(),this->inputComponent, [this]() {s_restartPlay();});
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