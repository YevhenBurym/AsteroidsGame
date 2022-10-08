//
// Created by Евгений on 22.07.2022.
//

#include "PauseState.h"

PauseState::PauseState(GameWindow *gameWindow) {
    this->gameWindow = gameWindow;

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

    int hMenu,wMenu;
    int hResume,wResume;
    this->gameWindow->getTextureManager()->getTextureSize("menu_button", wMenu, hMenu);
    this->gameWindow->getTextureManager()->getTextureSize("resume_button", wResume, hResume);
    double xMenu = this->gameWindow->getSize().width / 2 - wMenu / 4;
    double yMenu = 2 * this->gameWindow->getSize().height / 5 - hMenu / 2;
    double xResume = this->gameWindow->getSize().width / 2 - wResume / 4;
    double yResume = 3 * this->gameWindow->getSize().height / 5 - hResume / 2;

    auto menuButton = new Button({xMenu, yMenu}, "menu_button", this->gameWindow->getTextureManager(),
                                 this->gameWindow->getInputHadler(), toMain);
    auto resumeButton = new Button({xResume, yResume}, "resume_button", this->gameWindow->getTextureManager(),
                                   this->gameWindow->getInputHadler(), toResume);
    this->menuButtons.push_back(menuButton);
    this->menuButtons.push_back(resumeButton);
    SDL_ShowCursor(SDL_ENABLE);
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

std::string PauseState::getStateID() const {
    return PauseState::pauseID;
}

PauseState::~PauseState() {
    SDL_ShowCursor(SDL_DISABLE);
    for (auto &button : this->menuButtons) {
        delete button;
    }
    this->menuButtons.clear();
}
