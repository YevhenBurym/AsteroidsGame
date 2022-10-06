//
// Created by Евгений on 22.07.2022.
//

#include "PauseState.h"

PauseState::PauseState(GameWindow *gameWindow) {
    this->gameWindow = gameWindow;
}

const std::string PauseState::pauseID = "PAUSE";

void PauseState::update() {
    for (auto &menuButton : this->menuButtons) {
        menuButton->update();
        if (this->gameWindow->getGameStateMachine()->needToErasePrevState()) {
            return;
        };
    }
}

void PauseState::render() {
    for (auto &menuButton : this->menuButtons) {
        menuButton->render();
    }
}

bool PauseState::onEnter() {
    SDL_ShowCursor(SDL_ENABLE);

    std::function<void()> toMain{
            [this]() {
                this->gameWindow->getGameStateMachine()->changeState(new MenuState(this->gameWindow));
            }
    };

    std::function<void()> toResume{
            [this]() {
                this->gameWindow->getGameStateMachine()->popState();
            }
    };
    auto menuButton = new Button({280, 150}, "menu_button", this->gameWindow->getTextureManager(),
                                 this->gameWindow->getInputHadler(), toMain);
    auto resumeButton = new Button({280, 350}, "resume_button", this->gameWindow->getTextureManager(),
                                   this->gameWindow->getInputHadler(), toResume);
    this->menuButtons.push_back(menuButton);
    this->menuButtons.push_back(resumeButton);
    return true;
}

bool PauseState::onExit() {
    //this->gameWindow->getInputHadler()->initMouseButtons();
    return true;
}

std::string PauseState::getStateID() const {
    return PauseState::pauseID;
}

PauseState::~PauseState() {
    for (auto &button : this->menuButtons) {
        delete button;
    }
    this->menuButtons.clear();
}
