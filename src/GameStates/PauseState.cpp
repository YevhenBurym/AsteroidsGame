//
// Created by Евгений on 22.07.2022.
//

#include "PauseState.h"

PauseState::PauseState(GameWindow* gameWindow) {
    this->gameWindow = gameWindow;
}

const std::string PauseState::pauseID = "PAUSE";

void PauseState::s_pauseToMain() {
    this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow));
}

void PauseState::s_resumePlay() {
    this->gameWindow->getGameStateMachine()->popState();
}

void PauseState::update() {
//    for (auto &button : this->menuButtons) {
//        button->update();
//    }
    for(int i = 0; i < this->menuButtons.size(); i++) {
        this->menuButtons[i]->update();
    }
}

void PauseState::render() {
    for(int i = 0; i < this->menuButtons.size(); i++) {
        this->menuButtons[i]->render();
    }
//    for (auto &button : this->menuButtons) {
//        button->render();
//    }
}

bool PauseState::onEnter() {
    SDL_ShowCursor(SDL_ENABLE);
    auto menuButton = new Button({280,150},"menu_button",this->gameWindow->getTextureManager(),this->gameWindow->getInputHadler(),[this]() { s_pauseToMain(); });
    auto resumeButton = new Button({280,350},"resume_button",this->gameWindow->getTextureManager(),this->gameWindow->getInputHadler(),[this]() { s_resumePlay(); });

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
    this->gameWindow->getInputHadler()->initMouseButtons();

    SDL_ShowCursor(SDL_DISABLE);
    std::cout << "exiting PauseState\n";
    return true;
}

std::string PauseState::getStateID() const {
    return PauseState::pauseID;
}