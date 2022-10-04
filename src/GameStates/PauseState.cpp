//
// Created by Евгений on 22.07.2022.
//

#include "PauseState.h"

PauseState::PauseState(GameWindow* gameWindow, InputComponent* inputComponent) {
    this->gameWindow = gameWindow;
    this->inputComponent = inputComponent;
}

const std::string PauseState::pauseID = "PAUSE";

void PauseState::s_pauseToMain() {
    this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow,this->inputComponent));
}

void PauseState::s_resumePlay() {
    this->gameWindow->getGameStateMachine()->popState();
}

void PauseState::update() {
    for (auto &button : this->menuButtons) {
        button->update();
    }
}

void PauseState::render() {
    for (auto &button : this->menuButtons) {
        button->render();
    }
}

bool PauseState::onEnter() {
    auto menuButton = new Button({220,100},"menu_button",this->gameWindow->getTextureManager(),this->inputComponent,[this]() { s_pauseToMain(); });
    auto resumeButton = new Button({220,300},"resume_button",this->gameWindow->getTextureManager(),this->inputComponent,[this]() { s_resumePlay(); });

    this->menuButtons.push_back(menuButton);
    this->menuButtons.push_back(resumeButton);
    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit() {
    for (auto &button : this->menuButtons) {
        delete button;
    }
    this->menuButtons.clear();
// reset the mouse button states to false
    this->inputComponent->initMouseButtons();
    std::cout << "exiting PauseState\n";
    return true;
}

std::string PauseState::getStateID() const {
    return PauseState::pauseID;
}